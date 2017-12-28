#include "compositemodel.h"
#include <glm/gtc/type_ptr.hpp>

void ModelComponent::calculateMatrix() {
	glm::mat4 unit;
	auto rotate = glm::toMat4(relativeOrientation);
	auto translate = glm::translate(unit, relativePos);
	rotate = glm::toMat4(mainOrientation) * translate * rotate;
	translate = glm::translate(unit, mainPos);
	this->matrix = translate * baseMatrix * rotate;
    model->setBaseMatrix(this->matrix);
}

void ModelComponent::setPosition(glm::vec3 position) {
    setRelativePosition(position);
}

void ModelComponent::setQuatRotation(glm::vec3 axis, GLfloat angle) {
	this->relativeOrientation = glm::angleAxis(angle, axis);
	calculateMatrix();
}

void ModelComponent::setOrientation(glm::quat orientation) {
	this->relativeOrientation = orientation;
	calculateMatrix();
}

void ModelComponent::render(GLuint matrixHandle, GLuint textureHandle) const {
    model->render(matrixHandle, textureHandle);
}

void ModelComponent::setBaseMatrix(glm::mat4 matrix) {
    this->baseMatrix = matrix;
    calculateMatrix();
}

void CompositeModel::setBaseMatrix(glm::mat4 matrix) {
    if (this->baseMatrix == matrix)
        return;
    this->baseMatrix = matrix;
    for(auto it = components.begin(); it != components.end(); ++it) {
        it->setBaseMatrix(matrix);
    }
}

void CompositeModel::setPosition(glm::vec3 position) {
    if (this->position == position)
        return;
    this->position = position;
    for(auto it = components.begin(); it != components.end(); ++it) {
        it->setMainPosition(position);
    }
}

void CompositeModel::setQuatRotation(glm::vec3 axis, GLfloat angle) {
	this->orientation = glm::angleAxis(angle, axis);
	for (auto it = components.begin(); it != components.end(); ++it) {
		it->setMainQuatRotation(axis, angle);
	}
}

void CompositeModel::setOrientation(glm::quat orientation) {
	this->orientation = orientation;
	for (auto it = components.begin(); it != components.end(); ++it) {
		it->setMainOrientation(orientation);
	}
}

void CompositeModel::render(GLuint matrixHandle, GLuint textureHandle) const {
    for(auto it = components.begin(); it != components.end(); ++it) {
        glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(it->getMatrix()));
        it->render(matrixHandle, textureHandle);
    }
}
