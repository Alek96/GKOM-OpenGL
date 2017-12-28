#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <glm/gtx/quaternion.hpp>
#include "model.h"

class SimpleModel : public Model {
    public:
        SimpleModel(const Mesh& mesh) : mesh(std::move(mesh)) {}
        
        void setBaseMatrix(glm::mat4 matrix);
        void setPosition(glm::vec3 position);
		void setQuatRotation(glm::vec3 axis, GLfloat angle);
		void setOrientation(glm::quat orientation);
        void render(GLuint matrixHandle, GLuint textureHandle) const;
        
        void calculateMatrix();
        
    protected:
        glm::vec3 position;
        glm::vec3 rotation;
		glm::quat orientation;

        Mesh mesh;
};
