#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#define LIGHT_CONTROL_SPEED 64

class Light {
private:
	glm::vec3 position;
	glm::vec3 color;
	GLfloat intensity;
	glm::vec3 diffuseColor;
	glm::vec3 ambientColor;
public:
	Light(glm::vec3 position, glm::vec3 color, GLfloat intensity) : position(position), color(color), intensity(intensity)
	{
		calculate();
	}
	void calculate() {
		diffuseColor = color*intensity;
		ambientColor = glm::normalize(color)*0.5f;
	}
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getDiffuseColor() const { return diffuseColor; }
	glm::vec3 getAmbientColor() const { return ambientColor; }

	void incrementIntensity(GLfloat delta) {
		if ((delta > 0 && intensity < 256) || (delta < 0 && intensity > 0)) {
			intensity += LIGHT_CONTROL_SPEED*delta;
			if (intensity < 0)
				intensity = 0;
			calculate();
		}
	}
};