#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <string>
using std::string;

class Window {
    private:
        GLFWwindow* window;
        const string title;
    public:
        Window(GLuint ver_major, GLuint ver_minor, string title, GLuint width, GLuint height);
        
        void swapBuffers();
        void pollEvents();
        int getKey(int key);
        bool shouldClose();
};
