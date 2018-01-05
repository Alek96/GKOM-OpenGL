#pragma once

#include <deque>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "simpleModel.h"

class ModelComponent : public Model {
private:
	glm::vec3 relativePos;
	glm::vec3 mainPos;
	glm::quat relativeOrientation;
	glm::quat mainOrientation;
	Model* model;

public:
	ModelComponent(const Mesh& mesh);
	ModelComponent(const Mesh& mesh, glm::vec3 relativePos, glm::vec3 mainPos);
	ModelComponent(Model* model);

	~ModelComponent();

	glm::vec3 getFixedPosition();
	void calculateMatrix();
	void setPosition(glm::vec3 position);
	void setQuatRotation(glm::vec3 axis, GLfloat angle);
	void setOrientation(glm::quat orientation);
	void setBaseMatrix(glm::mat4 matrix);

	void setTexture(Texture texture);

	void setRelativePosition(glm::vec3 relativePos);

	void setMainPosition(glm::vec3 mainPos);

	void setMainQuatRotation(glm::vec3 axis, GLfloat angle);

	void setMainOrientation(glm::quat orientation);

	void render(GLuint matrixHandle, GLuint textureHandle) const;
};