#include "model.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

void Model::setPosition(glm::vec3 position) {
	if (this->position == position)
		return;
	this->position = position;
	calculateMatrix();
}

void Model::setQuatRotation(glm::vec3 axis, GLfloat angle) {
	orientation = glm::angleAxis(angle, axis);
	calculateMatrix();
}

void Model::setOrientation(glm::quat orientation) {
	this->orientation = orientation;
	calculateMatrix();
}

void Model::setExternalMatrix(glm::mat4 matrix) {
	this->externalMatrix = matrix;
	calculateMatrix();
}

const glm::vec3 Model::getTruePosition() const {
	return glm::vec3(matrix[3]);
}

const glm::vec3 Model::getPosition() const {
	return position;
}

const glm::quat Model::getOrientation() const {
	return orientation;
}

const glm::mat4& Model::getMatrix() const {
	return matrix;
}

const glm::mat4& Model::getExternalMatrix() const {
	return externalMatrix;
}

void Model::setMatrix(glm::mat4 matrix) {
	this->matrix = matrix;
}
