#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
    private:
        GLuint id;
    public:
        Texture(std::string filename);
        GLuint getID() const { return id; }
        
};

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