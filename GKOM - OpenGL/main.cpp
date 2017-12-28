#include "including.h"


// Other includes
#include "Shader.h"
#include "camera.h"
#include "Cylinder.h"
#include "Saw.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double posX, double posY);

void scroll_callback(GLFWwindow*, double, double);
void init();
void do_movement();

GLuint activateText(char*);

// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;

bool keys[1024];

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLFWwindow* window;









// The MAIN function, from here we start the application and run the game loop
int main()
{
	init();
	Shader ourShader("default.vs", "default.frag");

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLfloat floorRoom[] = {
		-4.0f, -3.0f, -4.0f,	0.0f, 0.0f,
		-4.0f, -3.0f, 4.0f,		0.0f, 0.5f,
		4.0f, -3.0f, 4.0f,		1.0f, 0.5f,

		4.0f, -3.0f, -4.0f,		1.0f, 0.0f,
		-4.0f, -3.0f, -4.0f,	0.0f, 0.0f,
		4.0f, -3.0f, 4.0f,		1.0f, 0.5f,

		-4.0f, 3.0f, -4.0f,		0.0f, 0.5f,
		-4.0f, 3.0f, 4.0f,		0.0f, 1.0f,
		4.0f, 3.0f, 4.0f,		1.0f, 1.0f,

		4.0f, 3.0f, -4.0f,		1.0f, 0.5f,
		-4.0f, 3.0f, -4.0f,		0.0f, 0.5f,
		4.0f, 3.0f, 4.0f,		1.0f, 1.0f

	};

	GLfloat walls[] = {


		-4.0f, -3.0f, -4.0f,	1.0f, 0.0f,
		-4.0f, 3.0f, -4.0f,		1.0f, 0.5f,
		-4.0f, 3.0f, 4.0f,		0.0f, 0.5f,

		-4.0f, -3.0f, -4.0f,	1.0f, 0.0f,
		-4.0f, -3.0f, 4.0f,		0.0f, 0.0f,
		-4.0f, 3.0f, 4.0f,		0.0f, 0.5f,

		4.0f, -3.0f, -4.0f,		1.0f, 0.0f,
		4.0f, -3.0f, 4.0f,		0.0f, 0.0f,
		4.0f, 3.0f, 4.0f,		0.0f, 0.5f,

		4.0f, 3.0f, -4.0f,		1.0f, 0.5f,
		4.0f, 3.0f, 4.0f,		0.0f, 0.5f,
		4.0f, -3.0f, -4.0f,		1.0f, 0.0f,
/////////////////////////////////////////////////////////////////// z dziurami
		-4.0f, -3.0f, -4.0f,	0.0f, 0.5f,
		4.0f, -3.0f, -4.0f,		1.0f, 0.5f,
		-4.0f, 3.0f, -4.0f,		0.0f, 1.0f,

		-4.0f, 3.0f, -4.0f,		0.0f, 1.0f,
		4.0f, 3.0f, -4.0f,		1.0f, 1.0f,
		4.0f, -3.0f, -4.0f,		1.0f, 0.5f,

		-4.0f, -3.0f, 4.0f,		0.0f, 0.5f,
		4.0f, -3.0f, 4.0f,		1.0f, 0.5f,
		-4.0f, 3.0f, 4.0f,		0.0f, 1.0f,

		-4.0f, 3.0f, 4.0f,		0.0f, 1.0f,
		4.0f, 3.0f, 4.0f,		1.0f, 1.0f,
		4.0f, -3.0f, 4.0f,		1.0f, 0.5f,


	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLfloat vertices1[] = {
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		10.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		10.0f, 5.0f, 0.0f,	1.0f, 1.0f,

		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 5.0f, 0.0f,	0.0f, 1.0f,
		10.f, 5.0f, 0.0f,	1.0f, 1.0f,
	};

glm::vec3 pillarsPos[] = {
	glm::vec3(-2.4f,  -1.5f,  -1.33f),
	glm::vec3(-2.4f,  -1.5f, -1.63f),
	glm::vec3(-1.6f, -1.5f, -1.33f),
	glm::vec3(-1.6f, -1.5f, -1.63f),
};


/////////////////////////////////////////////////////// VAO i VBO
	GLuint VBO[6], VAO[6];
	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);

	Saw ourSaw = Saw(20, 2.0f, 0.25f, VAO[0], VBO[0]);
	Cylinder log = Cylinder(0.25f, 12, 2.0f, VAO[1], VBO[1]);
	Cylinder pillar = Cylinder(0.1f, 8, 1.2f, VAO[2], VBO[2]);

	log.bindColor();


	bindText(VAO[3], VBO[3], vertices, 180);
	bindText(VAO[4], VBO[4], floorRoom, 60);
	bindText(VAO[5], VBO[5], walls, 120);


	GLuint texture1, texture2, texture3;
	texture1 = activateText("wall2.png");
	texture2 = activateText("awesomeface.png");
	texture3 = activateText("whole.png");
 

	GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");


////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 model;


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);


		ourSaw.draw(modelLoc, vertexColorLocation, &log, deltaTime);

////////////////////////////////////////////bela drewna
		
		log.drawLog(modelLoc, vertexColorLocation, &ourSaw, deltaTime);

		pillar.drawPillars(modelLoc, vertexColorLocation, pillarsPos);

/////////////////////////////pokoj

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(vertexColorLocation, 0.9f, 0.9f, 0.9f, 1.0f);
	

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		glUniform4f(vertexColorLocation, 0.9f, 0.9f, 0.9f, 0.3f);
		glBindVertexArray(VAO[4]);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glUniform4f(vertexColorLocation, 0.4f, 0.6f, 0.7f, 0.5f);

		glBindVertexArray(VAO[5]);
		glDrawArrays(GL_TRIANGLES, 0, 24);

		

		

/*		glBindVertexArray(VAO[1]);
		glUniform4f(vertexColorLocation, 0.6f, 0.6f, 0.6f, 0.0f);

		for (GLuint i = 0 ; i < 10 ; ++i)
		{
			glm::mat4 model;
			model = translate(model, cubePositions[i]);
			GLfloat angle = i * glm::radians(20.0f);
			if(i % 3 == 0)
				angle = (i+1) * sin(glfwGetTime());
			model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/



////////////////////////////////////////// podstawa
		drawBasis(modelLoc, VAO[3], vertexColorLocation);


		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


void mouse_callback(GLFWwindow* window, double posX, double posY)
{
	if (firstMouse)
	{
		lastX = posX;
		lastY = posY;
		firstMouse = false;
	}

	GLfloat xoffset = posX - lastX;
	GLfloat yoffset = lastY - posY; 

	lastX = posX;
	lastY = posY;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double offsetX, double offsetY)
{
	camera.ProcessMouseScroll(offsetY);
}

GLuint activateText(char* name)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
											// Set the texture wrapping parameters


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(name, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	return texture;

}

void init()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Trak poprzeczny", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);


	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetScrollCallback(window, scroll_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);


}

