#include "render.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Render::Render(Camera& camera) : camera(camera) {
    ShaderProgram tmp("Shader/gl_06.vert", "Shader/gl_06.frag");
	ShaderProgram tmp2("Shader/skybox.vert", "Shader/skybox.frag");
    mainShader = tmp.get_programID();
	skyboxShader = tmp2.get_programID();
    modelHandle = glGetUniformLocation(mainShader, "model");
    viewHandle = glGetUniformLocation(mainShader, "view");
    projectionHandle = glGetUniformLocation(mainShader, "projection");
    textureHandle = glGetUniformLocation(mainShader, "texture0");
	skyboxViewHandle = glGetUniformLocation(skyboxShader, "view");
	skyboxProjectionHandle = glGetUniformLocation(skyboxShader, "projection");
	skyboxTextureHandle = glGetUniformLocation(skyboxShader, "skybox");
	lightPositionHandle = glGetUniformLocation(mainShader, "lightPosition");
	lightDiffuseColorHandle = glGetUniformLocation(mainShader, "lightDiffuseColor");
	lightAmbientColorHandle = glGetUniformLocation(mainShader, "lightAmbientColor");
	viewPositionHandle = glGetUniformLocation(mainShader, "viewPosition");
}

void Render::renderModel(const Model* model) {
     model->render(modelHandle, textureHandle);
}

void Render::renderView() {
    glUseProgram(mainShader);
    glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
    glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(camera.getView()));

	glUniform3fv(viewPositionHandle, 1, glm::value_ptr(camera.getPosition()));
	glEnable(GL_LIGHTING);

}

void Render::renderSkybox(const Skybox& skybox) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 skyboxView(glm::mat3(camera.getView()));

	glDepthMask(GL_FALSE);
	glUseProgram(skyboxShader);

	glUniformMatrix4fv(skyboxProjectionHandle, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
	glUniformMatrix4fv(skyboxViewHandle, 1, GL_FALSE, glm::value_ptr(skyboxView));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getID());

	skybox.render();
	glDepthMask(GL_TRUE);
}

void Render::renderLight(const Light& light) {
	glUniform3fv(lightPositionHandle, 1, glm::value_ptr(light.getPosition()));
	glUniform3fv(lightAmbientColorHandle, 1, glm::value_ptr(light.getAmbientColor()));
	glUniform3fv(lightDiffuseColorHandle, 1, glm::value_ptr(light.getDiffuseColor()));
}
