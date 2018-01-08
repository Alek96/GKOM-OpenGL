#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "vertex.h"

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, glm::vec3 meshColor);
	Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices, glm::vec3 meshColor);
	void render() const;
private:
	void init();
};
