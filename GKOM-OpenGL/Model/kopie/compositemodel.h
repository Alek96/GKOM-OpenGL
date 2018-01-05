#pragma once
#include <deque>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "modelComponent.h"


class CompositeModel : public Model {
    private:
        glm::vec3 position;
		glm::quat orientation;
        std::deque<ModelComponent> components;
    public:
        void addMesh(const Mesh& mesh, glm::vec3 relativePos) { components.emplace_back(mesh, relativePos, position); }
        void addModel(Model* model) { components.emplace_back(model); }
        void addModel(Model& model) { components.emplace_back(&model); }
        void setPosition(glm::vec3 position);
		void setQuatRotation(glm::vec3 axis, GLfloat angle);
		void setOrientation(glm::quat orientation);
        const std::deque<ModelComponent>& getComponents() const { return components; }
        void render(GLuint matrixHandle, GLuint textureHandle) const;
        void setBaseMatrix(glm::mat4 matrix);
        ModelComponent& operator[](int index) { return components[index]; }
        
};
