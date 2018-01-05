#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include "../Model/model.h"
#include "../Shader/shprogram.h"
#include "../Texture/texture.h"
#include "../Light/light.h"
#include "camera.h"

class Render {
    private:
        GLuint mainShader;
		GLuint skyboxShader;
        GLint modelHandle;
        GLuint viewHandle;
        GLuint projectionHandle;
        GLuint textureHandle;
		GLuint skyboxViewHandle;
		GLuint skyboxProjectionHandle;
		GLuint skyboxTextureHandle;
		GLuint lightPositionHandle;
		GLuint lightDiffuseColorHandle;
		GLuint lightAmbientColorHandle;
		GLuint viewPositionHandle;
		Camera& camera;
        
    public:
        Render(Camera& camera);
        void renderModel(const Model* model);
        void renderView();
		void renderSkybox(const Skybox& skybox);
		void renderLight(const Light& light);
};
