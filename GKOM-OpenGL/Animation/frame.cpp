#include "frame.h"


Frame::Frame(GLfloat startTime, glm::vec3 position) {
	setStartTime(startTime);
	setPosition(position);
}

void Frame::setPosition(glm::vec3 position) {
	this->position = position;
}

void Frame::setStartTime(GLfloat startTime) {
	this->startTime = startTime;
}

const glm::vec3 Frame::getPosition() const {
	return position;
}

const GLfloat Frame::getStartTime() const
{
	return startTime;
}
