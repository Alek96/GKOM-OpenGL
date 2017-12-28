#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <vector>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textCoord;
    glm::vec3 normal;
    

    Vertex() {};

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textCoord) : position(position), normal(normal), textCoord(textCoord) {}
    void setColor(glm::vec3 color) { this->color = color; }
};

class Mesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
    public:
        Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices, glm::vec3 meshColor);
        void render() const;
};
