#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define CAMERA_SPEED 1.0f

class Camera {
    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 position;
        glm::vec3 target;
        GLfloat hAngle;
        GLfloat vAngle;
        GLfloat distance;
        void setPosition();
    public:
        Camera(glm::vec3 target, GLfloat hAngle, GLfloat vAngle, GLfloat distance);
        const glm::mat4& getProjection() const { return projection; }
        const glm::mat4& getView() const { return view; }
		const glm::vec3& getPosition() const { return position; }
        void setDistance(GLfloat distance);
        void incrementVAngle(GLfloat delta);
        void incrementHAngle(GLfloat delta);
        void incrementDistance(GLfloat delta);
};
