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
	auto translate = glm::translate(unit, position);
	auto rotate = glm::toMat4(orientation);

	matrix = externalMatrix * translate * rotate;

	for (auto it = components.begin(); it != components.end(); ++it) {
		(*it)->setExternalMatrix(matrix);
	}
}

void ModelComposite::render(GLuint matrixHandle, GLuint textureHandle) const {
    for(auto it = components.begin(); it != components.end(); ++it) {
        //glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, glm::value_ptr(it->getMatrix()));
		(*it)->render(matrixHandle, textureHandle);
    }
}
