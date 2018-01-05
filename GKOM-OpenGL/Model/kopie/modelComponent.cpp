#include "modelComponent.h"
#include <glm/gtc/type_ptr.hpp>


ModelComponent::ModelComponent(const Mesh& mesh) 
	: model(new SimpleModel(mesh)) {}
ModelComponent::ModelComponent(const Mesh& mesh, glm::vec3 relativePos, glm::vec3 mainPos) 
	: model(new SimpleModel(mesh)), relativePos(relativePos), mainPos(mainPos) {
	calculateMatrix();
}
ModelComponent::ModelComponent(Model* model) 
	: model(model) {}

ModelComponent::~ModelComponent() { 
	delete model; 
}

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

glm::vec3 ModelComponent::getFixedPosition() {
	return glm::vec3(this->matrix[3]);
}

void ModelComponent::setTexture(Texture texture) { 
	model->setTexture(texture); 
}

void ModelComponent::setRelativePosition(glm::vec3 relativePos) {
	this->relativePos = relativePos;
	calculateMatrix();
}

void ModelComponent::setMainPosition(glm::vec3 mainPos) {
	this->mainPos = mainPos;
	calculateMatrix();
}

void ModelComponent::setMainQuatRotation(glm::vec3 axis, GLfloat angle) {
	mainOrientation = glm::angleAxis(angle, axis);
	calculateMatrix();
}

void ModelComponent::setMainOrientation(glm::quat orientation) {
	mainOrientation = orientation;
	calculateMatrix();
}