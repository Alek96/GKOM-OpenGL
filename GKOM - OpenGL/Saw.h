#pragma once
#include "including.h"

class Cylinder;

class Saw 
{
private:
	GLfloat side, level, *tab;
	GLuint vao, vbo;
	bool left, up, stop;
	int number;
	
public:
	Saw(int pieces, GLfloat width, GLfloat height, GLuint VAO, GLuint VBO);
	~Saw();
	void draw(GLint modelLoc, GLint vertexColorLocation, Cylinder* , GLfloat);
	void setStop(bool);
	bool getStop();

};