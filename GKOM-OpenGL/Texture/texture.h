#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <string>

class Texture {
    private:
        GLuint id;
    public:
        Texture(std::string filename);
        GLuint getID() const { return id; }
};