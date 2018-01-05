#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include "mesh.h"
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Texture/texture.h"


class Model 
{
public:
	virtual void setPosition(glm::vec3 position);
	virtual glm::vec3 getPosition();
	virtual void setOrientation(glm::quat orientation);
	virtual void setQuatRotation(glm::vec3 axis, GLfloat angle);
	virtual void setExternalMatrix(glm::mat4 matrix);
	virtual void calculateMatrix() = 0;
	virtual void render(GLuint matrixHandle, GLuint textureHandle) const = 0;
	virtual void setTexture(Texture texture) {};

	const glm::mat4& getMatrix() const;

protected:
	glm::mat4 matrix;
	glm::mat4 externalMatrix;
	glm::vec3 position;
	glm::quat orientation;
};
