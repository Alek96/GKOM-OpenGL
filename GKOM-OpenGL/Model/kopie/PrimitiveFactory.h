#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include "mesh.h"

class PrimitiveFactory {
public:
    static Mesh createBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 color);
    static Mesh createCylinder(GLfloat radius, GLfloat height, GLuint segments, glm::vec3 color);
    static Mesh createPlane(GLfloat width, GLfloat depth, glm::vec3 color);
    static Mesh createSaw(GLfloat width, GLfloat depth, GLuint triangles, glm::vec3 color);
    static Mesh createCircle(GLfloat radius, GLuint segments, glm::vec3 color);
};
