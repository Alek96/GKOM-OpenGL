#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "simpleModel.h"

SimpleModel::SimpleModel(const Mesh& mesh) 
	: mesh(std::move(mesh)) {}

void SimpleModel::setPosition(glm::vec3 position) {
    if (this->position == position)
        return;
    this->position = position;
    calculateMatrix();
}

void SimpleModel::setQuatRotation(glm::vec3 axis, GLfloat angle) {
	orientation = glm::angleAxis(angle, axis);
	calculateMatrix();
}

void SimpleModel::setOrientation(glm::quat orientation) {
	this->orientation = orientation;
	calculateMatrix();
}

void SimpleModel::setBaseMatrix(glm::mat4 matrix) {
    this->baseMatrix = matrix;
    calculateMatrix();
}

void SimpleModel::calculateMatrix() {
	glm::mat4 unit;
    auto translate = glm::translate(unit, position);
	auto rotate = glm::toMat4(orientation);

    this->matrix = translate * baseMatrix * rotate;
}


void SimpleModel::render(GLuint matrixHandle, GLuint textureHandle) const {
    glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    mesh.render();
}
