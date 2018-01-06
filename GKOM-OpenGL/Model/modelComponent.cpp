#include "modelComponent.h"
#include <glm/gtc/type_ptr.hpp>


ModelComponent::ModelComponent(const Mesh& mesh) 
	: mesh(std::move(mesh)) {}

void ModelComponent::calculateMatrix() {
	glm::mat4 unit;
	auto translate = glm::translate(unit, getPosition());
	auto rotate = glm::toMat4(getOrientation());

	setMatrix(getExternalMatrix() * translate * rotate);
}

void ModelComponent::setTexture(Texture texture) {
	textureID = texture.getID();
}

void ModelComponent::render(GLuint matrixHandle, GLuint textureHandle) const {
	glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(getMatrix()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	mesh.render();
}