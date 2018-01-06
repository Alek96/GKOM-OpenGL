#pragma once
#include <deque>
#include "frame.h"
#include "../Model/model.h"

class Animation
{
public:
	Animation(Model* model);
	~Animation();

	void addFrame(Frame* frame);
	void setTime(GLfloat time);
	void animate();

private:
	Model* model;
	std::deque<Frame*> frames;
	std::deque<Frame*>::iterator actFrame;
	GLfloat time;
};