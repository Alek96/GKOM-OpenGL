#pragma once
#ifdef _WIN32
#define GLEW_STATIC
#endif
#include <map>
#include "render.h"
#include "../Model/compositemodel.h"
#include "../Light/light.h"
#include "parameters.h"

struct AnimationState {
	GLfloat time;
	glm::vec3 position;
	AnimationState(GLfloat time, glm::vec3 position) : time(time), position(position) {}
	AnimationState() {}
};

class Scene {
    private:
        std::deque<Model*> models;
		GLfloat timePosition;
		std::map<Model*, std::vector<AnimationState>> animation;
		Model* saw;
		Model* halvedLog;
		Model* log1;
		Model* log2;
		Light* light;
        Texture treeTrunk;
        Texture archWood;
        Texture treeStump;
		Texture groundForest;
        Texture blank;
		void initModels();
		void initAnimations();
		void animate();

    public:
        Scene() : treeTrunk("Texture/bark.jpg"), 
				archWood("Texture/arch_wood2.jpg"), 
				treeStump("Texture/tree_stump.jpg"),
				blank("Texture/blank.jpg"),
				groundForest("Texture/Skybox/negy.jpg"),
				timePosition(0) { init(); }
        ~Scene();
		void incrementTime(GLfloat delta);
		Light& getLight() { return *light; }
        void init();
        void render(Render renderer);
        CompositeModel* createLog();
};
