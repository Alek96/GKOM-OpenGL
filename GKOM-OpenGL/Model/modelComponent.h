#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "model.h"

class ModelComponent 
	: public Model 
{
private:
	Mesh mesh;
	GLuint textureID;

public:
	ModelComponent(const Mesh& mesh);

	void calculateMatrix();
	void setTexture(Texture texture);
	void render(GLuint matrixHandle, GLuint textureHandle) const;
};