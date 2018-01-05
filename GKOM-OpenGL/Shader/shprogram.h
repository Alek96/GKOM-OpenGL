#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <sstream>

class ShaderProgram
{
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Use the program
	void Use() const;

	// returns program ID
	GLuint get_programID() const;

private:
	std::string read_shader_code(const GLchar* shaderPath);
	GLuint compile_shader(const GLchar* shaderCode, GLenum shaderType);
};
