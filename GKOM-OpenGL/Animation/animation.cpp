#include "animation.h"
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>

Animation::Animation(Model* model)
	: model(model)
{}

Animation::~Animation() {
	for (auto it = frames.begin(); it != frames.end(); ++it)
		delete *it;
}

void Animation::addFrame(Frame* frame) {
	frames.push_back(frame);
	actFrame = frames.begin();
}

void Animation::setTime(GLfloat time) {
	this->time = time;
}

void Animation::animate() {
	if (frames.empty())
		return;

	for (auto it = frames.begin(); it != frames.end(); ++it)
	{
		if ((*it)->getStartTime() > time) {
			Frame* frame = *(it - 1);
			Frame* nextFrame = *(it);
			GLfloat param = (time - frame->getStartTime()) / (nextFrame->getStartTime() - frame->getStartTime());
			model->setPosition(glm::mix(frame->getPosition(), nextFrame->getPosition(), param));
			break;
		}
	}
}