#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include "mesh.h"
#include <glm/mat4x4.hpp>
#include "../Texture/texture.h"


class Model {
public:
    virtual void setPosition(glm::vec3 position) = 0;
	virtual void setOrientation(glm::quat orientation) = 0;
	virtual void setQuatRotation(glm::vec3 axis, GLfloat angle) = 0;
    virtual void render(GLuint matrixHandle, GLuint textureHandle) const = 0;
    virtual void setBaseMatrix(glm::mat4 matrix) = 0;
    virtual void setTexture(Texture texture) { textureID = texture.getID(); }

    const glm::mat4& getMatrix() const { return matrix; }

protected:
    glm::mat4 matrix;
    glm::mat4 baseMatrix;
    GLuint textureID;
};
