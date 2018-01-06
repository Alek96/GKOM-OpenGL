#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <glm/vec3.hpp>


class Frame
{
public:
	Frame(GLfloat startTime, glm::vec3 position);

	void setPosition(glm::vec3 position);
	void setStartTime(GLfloat startTime);
	const glm::vec3 getPosition() const;
	const GLfloat getStartTime() const;

private:
	GLfloat startTime;
	glm::vec3 position;
};