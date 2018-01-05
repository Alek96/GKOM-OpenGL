#pragma once
#include <deque>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "model.h"


class ModelComposite 
	: public Model 
{
private:
	std::deque<Model*> components;
public:
	~ModelComposite();
	void add(Model* model);
	void calculateMatrix();
	void render(GLuint matrixHandle, GLuint textureHandle) const;

	const std::deque<Model*>& getComponents() const { return components; }
	Model* operator[](int index) { return components[index]; }
};
