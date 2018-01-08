#include "modelComposite.h"
#include <glm/gtc/type_ptr.hpp>

ModelComposite::~ModelComposite(){
	for (auto it = components.begin(); it != components.end(); ++it) {
		delete *it;
	}
}

void ModelComposite::add(Model* model) {
	components.push_back(model);
}

void ModelComposite::calculateMatrix() {
	glm::mat4 unit;
	auto translate = glm::translate(unit, getPosition());
	auto rotate = glm::toMat4(getOrientation());

	setMatrix(getExternalMatrix() * translate * rotate);

	for (auto it = components.begin(); it != components.end(); ++it) {
		(*it)->setExternalMatrix(getMatrix());
	}
}

void ModelComposite::render(GLuint matrixHandle, GLuint textureHandle) const {
    for(auto it = components.begin(); it != components.end(); ++it) {
		(*it)->render(matrixHandle, textureHandle);
    }
}

Model* ModelComposite::copy() {
	ModelComposite* newModel = new ModelComposite();
	for (auto it = components.begin(); it != components.end(); ++it) {
		newModel->add((*it)->copy());
	}
	newModel->setPosition(getPosition());
	newModel->setOrientation(getOrientation());
	newModel->setExternalMatrix(getExternalMatrix());

	return newModel;
}
