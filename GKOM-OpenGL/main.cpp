#ifdef _WIN32
#define GLEW_STATIC
#endif


#include <iostream>
#include <vector>
#ifdef _WIN32
using namespace std;
#else
#include "vs_adapter.h"
#endif
#define GL_MAJOR 3
#define GL_MINOR 0


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtx/transform.hpp>
 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

 // Model
#include "Model/PrimitiveFactory.h"
#include "Model/modelComposite.h"
// Shader
#include "Shader/shprogram.h"
// Window
#include "Window/window.h"
// Scene
#include "Scene/render.h"
#include "Scene/camera.h"
#include "Scene/scene.h"
// Texture
#include "Texture/texture.h"
#include "Texture/skybox.h"

#define CLEAR_COLOR 100.0f/255, 120.0f/255, 235.0f/255


const GLuint WIDTH = 1400, HEIGHT = 1000;

int main() {
    Window window(GL_MAJOR, GL_MINOR, "SawMill", WIDTH, HEIGHT);        
    Scene scene{};
	Light& light = scene.getLight();
    Camera camera(glm::vec3(0,0,0), 1.3f, 0.5f, 48.0f);
	Render render(camera);
	std::vector<std::string> skyboxNames = { "Texture/Skybox/posx.jpg", 
											"Texture/Skybox/negx.jpg", 
											"Texture/Skybox/posy.jpg", 
											"Texture/Skybox/negy.jpg", 
											"Texture/Skybox/posz.jpg", 
											"Texture/Skybox/negz.jpg" };
	Skybox skybox(skyboxNames);
    
    GLfloat delta = 0;
    GLfloat lastFrame = (GLfloat) glfwGetTime();
    
    glClearColor(CLEAR_COLOR, 1.0f);
    
    do{
        GLfloat currentFrame = (GLfloat) glfwGetTime();
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        window.pollEvents();
		scene.incrementTime(delta);
        
        if (window.getKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.incrementHAngle(-delta);
        if (window.getKey(GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.incrementHAngle(delta);
        if (window.getKey(GLFW_KEY_UP) == GLFW_PRESS)
            camera.incrementVAngle(delta);
        if (window.getKey(GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.incrementVAngle(-delta);
        if (window.getKey(GLFW_KEY_Z) == GLFW_PRESS)
            camera.incrementDistance(-delta);
        if (window.getKey(GLFW_KEY_X) == GLFW_PRESS)
            camera.incrementDistance(delta);
		if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
			light.incrementIntensity(-delta);
		if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
			light.incrementIntensity(delta);

		render.renderSkybox(skybox);
        render.renderView();
        scene.render(render);
		
        
        window.swapBuffers();
        window.pollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( window.getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		window.shouldClose() == 0 );
}
