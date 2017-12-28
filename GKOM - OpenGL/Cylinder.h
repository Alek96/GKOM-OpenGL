#pragma once
#include "including.h"
#include "Saw.h"

class Cylinder
{
private:
	int pieces, toDraw, logNum;
	bool stop;
	GLfloat move, *tab;
	GLuint vao, vbo;

public:
	Cylinder(GLfloat radius, int pieces, GLfloat height, GLuint, GLuint);
	~Cylinder();
	void drawLog(GLint modelLoc, GLint vertexColorLocation, Saw *saw, GLfloat delta);
	void drawPillars(GLint modelLoc, GLint colorLoc, glm::vec3 *positions);
	void bindColor();
	void setStop(bool);
	void setMove(GLfloat);
	void setLogNum(int);
	int getLogNum();
	bool getStop();
};



void drawBasis(GLint modelLoc, GLuint VAO, GLint vertexColorLocation);

void bindText(GLuint VAO, GLuint VBO, GLfloat* , int);

void bind(GLuint VAO, GLuint VBO, GLfloat* floor, int);

