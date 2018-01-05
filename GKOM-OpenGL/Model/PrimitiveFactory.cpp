#include <glm/gtc/constants.hpp>
#include <cmath>
#include <glm/geometric.hpp>
#include "PrimitiveFactory.h"

Mesh PrimitiveFactory::createBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 color) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17,
                                18, 18, 17, 19, 20, 21, 22, 22, 21, 23,};
    
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 0, 1), glm::vec2(1, 1));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(1, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, 0, -1), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(0, 1, 0), glm::vec2(1, 1));
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(0, -1, 0), glm::vec2(1, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(1, 0, 0), glm::vec2(1, 1));
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, -0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * height, 0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, -0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * height, 0.5 * depth), glm::vec3(-1, 0, 0), glm::vec2(1, 1));
    
    return Mesh(std::move(vertices), std::move(indices), color);
}

Mesh PrimitiveFactory::createPlane(GLfloat width, GLfloat depth, glm::vec3 color) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{0,1,2,1,3,2};
    vertices.emplace_back(glm::vec3(-0.5 * width, -0.5 * depth, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0));
    vertices.emplace_back(glm::vec3(0.5 * width, -0.5 * depth, 0), glm::vec3(0, 0, 1), glm::vec2(1, 0));
    vertices.emplace_back(glm::vec3(-0.5 * width, 0.5 * depth, 0), glm::vec3(0, 0, 1), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5 * width, 0.5 * depth, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1));

    return Mesh(std::move(vertices), std::move(indices), color);
}

Mesh PrimitiveFactory::createSaw(GLfloat width, GLfloat depth, GLuint triangles, glm::vec3 color) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLfloat triangleDelta = width*0.5f / (triangles-1);
    GLuint i;
    
    // triangle vertices
    vertices.emplace_back(glm::vec3(-0.5*width, -0.5*depth, 0), glm::vec3(0,0,1), glm::vec2(0,0.2));
    vertices.emplace_back(glm::vec3(-0.5*width, -0.75*depth, 0), glm::vec3(0,0,1), glm::vec2(0,0));
    for(i = 2; i < 2*triangles - 1; ++i) {
        if(i % 2 == 0) {
            vertices.emplace_back(glm::vec3(-0.5*width + (i-1)*triangleDelta, -0.5*depth, 0), glm::vec3(0, 0, 1), glm::vec2((i-1)*0.5/(triangles-1), 0.2));
        }
        else {
            vertices.emplace_back(glm::vec3(-0.5*width + (i-1)*triangleDelta, -0.75*depth, 0), glm::vec3(0, 0, 1), glm::vec2((i-1)*0.5/(triangles-1), 0));
        }
    }
    vertices.emplace_back(glm::vec3(0.5*width, -0.75*depth, 0), glm::vec3(0,0,1), glm::vec2(0,0));
    vertices.emplace_back(glm::vec3(0.5*width, -0.5*depth, 0), glm::vec3(0,0,1), glm::vec2(0,0.2));
    
    // plane vertices
    vertices.emplace_back(glm::vec3(-0.5*width, 0.5*depth, 0), glm::vec3(0, 0, 1), glm::vec2(0, 1));
    vertices.emplace_back(glm::vec3(0.5*width, 0.5*depth, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1));
    
    // indices
    for(i = 0; i < triangles; ++i) {
        indices.emplace_back(2*i);
        indices.emplace_back(2*i + 1);
        indices.emplace_back(2*i + 2);
        
        indices.emplace_back(2*i);
        indices.emplace_back(2*i + 2);
        indices.emplace_back(2*triangles + 1);
    }
    indices.emplace_back(2*triangles);
    indices.emplace_back(2*triangles + 2);
    indices.emplace_back(2*triangles + 1);
    
    return Mesh(std::move(vertices), std::move(indices), color);
}

Mesh PrimitiveFactory::createCylinder(GLfloat radius, GLfloat height, GLuint segments, glm::vec3 color) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    float deltaAngle = glm::two_pi<float>() / segments;
    
    // side indices
    for (GLuint i = 0; i < segments - 1; ++i) {
        indices.emplace_back(2*i);
        indices.emplace_back(2*i + 2);
        indices.emplace_back(2*i + 1);
        
        indices.emplace_back(2*i + 2);
        indices.emplace_back(2*i + 3);
        indices.emplace_back(2*i + 1);
    }
    
    indices.emplace_back(2*(segments - 1));
    indices.emplace_back(0);
    indices.emplace_back(2*(segments - 1) + 1);
    
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(2*(segments - 1) + 1);
    
    // base indices
    for (GLuint i = 1; i < segments - 1; ++i) {
        indices.emplace_back(0);
        indices.emplace_back(2*(i+1));
        indices.emplace_back(2*i);
        
        indices.emplace_back(1);
        indices.emplace_back(2*(i+1)+1);
        indices.emplace_back(2*i+1);
    }
    
    // vertices
    for (GLuint i = 0; i < segments; ++i) {
        float x = radius * std::cos(deltaAngle * i);
        float y = radius * std::sin(deltaAngle * i);
		//vertices.emplace_back(glm::vec3(x, y, -height / 2), glm::normalize(glm::vec3(x, y, 0)), glm::vec2((float) i / segments, 0));
		//vertices.emplace_back(glm::vec3(x, y, height / 2), glm::normalize(glm::vec3(x, y, 0)), glm::vec2((float)i / segments, 1));

        vertices.emplace_back(glm::vec3(x, y, -height / 2), mix(glm::normalize(glm::vec3(x, y, 0)), glm::vec3(0, 0, -1), 0.5), glm::vec2((float) i / segments, 0));
		vertices.emplace_back(glm::vec3(x, y, height / 2), mix(glm::normalize(glm::vec3(x, y, 0)), glm::vec3(0, 0, 1), 0.5), glm::vec2((float)i / segments, 1));
    }

    return Mesh(std::move(vertices), std::move(indices), color);
}

Mesh PrimitiveFactory::createCircle(GLfloat radius, GLuint segments, glm::vec3 color) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    float deltaAngle = glm::two_pi<float>() / segments;

    for (GLuint i = 1; i < segments - 1; ++i) {
        indices.emplace_back(0);
        indices.emplace_back(i+1);
        indices.emplace_back(i);
    }
    
    for (GLuint i = 0; i < segments; ++i) {
        float x = radius * std::cos(deltaAngle * i);
        float y = radius * std::sin(deltaAngle * i);
		//vertices.emplace_back(glm::vec3(x, y, 0), glm::normalize(glm::vec3(x, y, 0)), glm::vec2(x*0.5 / radius + 0.5, y*0.5 / radius + 0.5));

		vertices.emplace_back(glm::vec3(x, y, 0), mix(glm::normalize(glm::vec3(x, y, 0)), glm::vec3(0, 0, 1), 0.5), glm::vec2(x*0.5 / radius + 0.5, y*0.5 / radius + 0.5));
    }
    
    return Mesh(std::move(vertices), std::move(indices), color);
}
