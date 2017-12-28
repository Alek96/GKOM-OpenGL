#include "camera.h"

Camera::Camera(glm::vec3 target, GLfloat hAngle, GLfloat vAngle, GLfloat distance) : target(target), hAngle(hAngle), vAngle(vAngle), distance(distance) {
    projection = glm::perspective(glm::radians(45.0f), (float) 800 / (float) 600, 0.1f, 300.0f);
    setPosition();
}

void Camera::setPosition() {
    position.x = (float) (distance * cos(hAngle));
    position.y = (float) (distance * sin(vAngle));
    position.z = (float) (distance * sin(hAngle));
    view = glm::lookAt(
        position,
        target,
        glm::vec3(0,1,0)
    );
}

void Camera::incrementVAngle(GLfloat delta) {
    if((delta > 0 && vAngle < glm::half_pi<float>()) || (delta < 0 && vAngle > 0.05)) {
        vAngle += CAMERA_SPEED*delta;
        setPosition();
    }
}
void Camera::incrementHAngle(GLfloat delta) {
    hAngle += CAMERA_SPEED*delta;
    if(hAngle > glm::two_pi<float>())
        hAngle -= glm::two_pi<float>();
    else if(hAngle < -glm::two_pi<float>())
        hAngle += glm::two_pi<float>();
    setPosition();
}

void Camera::incrementDistance(GLfloat delta) {
    if((delta > 0 && distance < 64) || (delta < 0 && distance > 0)) {
        distance += CAMERA_SPEED*20*delta;
        setPosition();
    }
}


