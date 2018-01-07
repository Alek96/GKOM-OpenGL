#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

class Skybox {
private:
	GLuint id;
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> vertices;
public:
	Skybox(std::vector<std::string> filenames);
	GLuint getID() const { return id; }
	void render() const;
};