#include "window.h"
#include <stdexcept>


Window::Window(GLuint ver_major, GLuint ver_minor, string title, GLuint width, GLuint height) {
    if (!glfwInit() ) {
        throw std::runtime_error("could not init glfw");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver_minor);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
    if( window == NULL ){
        glfwTerminate();
        throw std::runtime_error("could not init window");
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("could not init glew");
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    //return 0;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

int Window::getKey(int key) {
    return glfwGetKey(window, key);
}

bool Window::shouldClose() {
    return (glfwWindowShouldClose(window) != 0);
}
