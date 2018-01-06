#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <map>
#include <deque>
#include "render.h"
#include "../Model/modelComposite.h"
#include "../Model/modelComponent.h"
#include "../Light/light.h"
#include "../Texture/texture.h"
#include "../Animation/animation.h"
#include "parameters.h"

class Scene {
    private:
		ModelComposite models;
		GLfloat timePosition;
		Light* light;
		std::deque<Animation> animations;
        Texture treeTrunk;
        Texture archWood;
        Texture treeStump;
		Texture groundForest;
        Texture blank;
		void initModels();
		void setPositionTexture(ModelComponent* model, glm::vec3 position, Texture texture);

    public:
        Scene() : treeTrunk("Texture/bark.jpg"), 
			archWood("Texture/arch_wood2.jpg"), 
			treeStump("Texture/tree_stump.jpg"),
			groundForest("Texture/ground1.jpg"),
			blank("Texture/blank.jpg"),
			timePosition(0) { init(); }
        ~Scene();
		void incrementTime(GLfloat delta);
		Light& getLight() { return *light; }
        void init();
        void render(Render renderer);
        ModelComposite* createLog();
};
