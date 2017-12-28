#pragma once
#include <deque>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "simplemodel.h"

class ModelComponent : public Model {
    private:
        glm::vec3 relativePos;
        glm::vec3 mainPos;
		glm::quat relativeOrientation;
		glm::quat mainOrientation;
        Model* model;
        
    public:
        ModelComponent(const Mesh& mesh) : model(new SimpleModel(mesh)) {}
        ModelComponent(const Mesh& mesh, glm::vec3 relativePos, glm::vec3 mainPos) : model(new SimpleModel(mesh)), relativePos(relativePos), mainPos(mainPos) {
            calculateMatrix();
        }
        ModelComponent(Model* model) : model(model) {}

		~ModelComponent() { delete model; }
        
		glm::vec3 getFixedPosition() { 
			return glm::vec3(this->matrix[3]);
		}
        void calculateMatrix();
        void setPosition(glm::vec3 position);
		void setQuatRotation(glm::vec3 axis, GLfloat angle);
		void setOrientation(glm::quat orientation);
        void setBaseMatrix(glm::mat4 matrix);
        
        void setTexture(Texture texture) { model->setTexture(texture); }
        
        void setRelativePosition(glm::vec3 relativePos) { 
            this->relativePos = relativePos;
            calculateMatrix();
        }

        void setMainPosition(glm::vec3 mainPos) { 
            this->mainPos = mainPos;
            calculateMatrix();
        }

		void setMainQuatRotation(glm::vec3 axis, GLfloat angle) {
			mainOrientation = glm::angleAxis(angle, axis);
			calculateMatrix();
		}

		void setMainOrientation(glm::quat orientation) {
			mainOrientation = orientation;
			calculateMatrix();
		}
        
        void render(GLuint matrixHandle, GLuint textureHandle) const;
        
        
};
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
