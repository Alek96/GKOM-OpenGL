#include <cmath>
#include <iterator>
#include <glm/gtc/quaternion.hpp>
#include "../Texture/texture.h"
#include "../Model/PrimitiveFactory.h"
#include "scene.h"

CompositeModel* Scene::createLog() {
    CompositeModel* log = new CompositeModel{};
    log->addMesh(PrimitiveFactory::createCylinder(LOG_RADIUS,LOG_WIDTH,CYLINDER_SEGMENTS, TRUNK_COLOR), glm::vec3(0.0f,0.0f,0.0f));
    log->addMesh(PrimitiveFactory::createCircle(LOG_INSIDE_RADIUS,CYLINDER_SEGMENTS, TRUNK_INSIDE_COLOR), glm::vec3(0,0,-LOG_WIDTH*0.5f - 0.01f));
    log->addMesh(PrimitiveFactory::createCircle(LOG_INSIDE_RADIUS,CYLINDER_SEGMENTS, TRUNK_INSIDE_COLOR), glm::vec3(0,0,LOG_WIDTH*0.5f + 0.01f));
    (*log)[0].setTexture(treeTrunk);
    (*log)[1].setTexture(treeStump);
	(*log)[1].setQuatRotation(glm::vec3(0, 1, 0), glm::pi<float>());
    (*log)[2].setTexture(treeStump);
    return log;
}

void Scene::init() {
	initModels();
	initAnimations();
}

void Scene::initAnimations(){
	animation.emplace(saw, std::vector<AnimationState>());
	animation.emplace(halvedLog, std::vector<AnimationState>());
	animation.emplace(log1, std::vector<AnimationState>());
	animation.emplace(log2, std::vector<AnimationState>());

	// halvedLog
	std::vector<AnimationState>& hLogFrames = animation[halvedLog];
	GLfloat logSpeed = -HALVED_LOG_Z * 0.5; // per second
	hLogFrames.emplace_back(0.0f, glm::vec3(0, LOG_Y, HALVED_LOG_Z));
	hLogFrames.emplace_back(2.0f, glm::vec3(0, LOG_Y, 0));
	hLogFrames.emplace_back(6.0f, glm::vec3(0, LOG_Y, 0));
	hLogFrames.emplace_back(8.0f, glm::vec3(0, LOG_Y, -HALVED_LOG_Z));
	hLogFrames.emplace_back(9.0f, glm::vec3(0, LOG_Y, -HALVED_LOG_Z + logSpeed * 1));
	
	// separate logs
	std::vector<AnimationState>& log1Frames = animation[log1];
	std::vector<AnimationState>& log2Frames = animation[log2];
	// log1
	log1Frames.emplace_back(0.0f, glm::vec3(0, 0, 0.5f*LOG_WIDTH));
	log1Frames.emplace_back(8.9f, glm::vec3(0, 0, 0.5f*LOG_WIDTH));
	log1Frames.emplace_back(9.0f, glm::vec3(0, -0.1f*logSpeed, 0.5f*LOG_WIDTH));
	log1Frames.emplace_back(9.07f, glm::vec3(0, -0.17f*logSpeed, 0.5f*LOG_WIDTH + 0.07f*logSpeed));
	log1Frames.emplace_back(9.22f, glm::vec3(0, -0.45f*logSpeed, 0.5f*LOG_WIDTH + 0.22f*logSpeed));
	log1Frames.emplace_back(9.4f, glm::vec3(0, -0.65f*logSpeed, 0.5f*LOG_WIDTH + 0.4*logSpeed));
	// log2
	log2Frames.emplace_back(0.0f, glm::vec3(0, 0, -0.5f*LOG_WIDTH));
	log2Frames.emplace_back(9.0f, glm::vec3(0, 0, -0.5f*LOG_WIDTH));
	log2Frames.emplace_back(9.9f, glm::vec3(0, 0, -0.5f*LOG_WIDTH + 0.9*logSpeed));
	log2Frames.emplace_back(10.07f, glm::vec3(0, -0.17f*logSpeed, -0.5f*LOG_WIDTH + 1.07f*logSpeed));
	log2Frames.emplace_back(10.22f, glm::vec3(0, -0.45f*logSpeed, -0.5f*LOG_WIDTH + 1.22f*logSpeed));
	log2Frames.emplace_back(10.4f, glm::vec3(0, -0.65f*logSpeed, -0.5f*LOG_WIDTH + 1.4f*logSpeed));

	// saw
	std::vector<AnimationState>& sawFrames = animation[saw];
	GLfloat sawUpY = SAW_Y;
	GLfloat sawDownY = SAW_Y - 6.75f + SAW_DEPTH + LOG_RADIUS;
	GLfloat sawLeftX = -0.75f;
	GLfloat sawRightX = 0.75f;
	glm::vec3 sawUp = glm::vec3(0, sawUpY, 0);
	sawFrames.emplace_back(0.0f, sawUp);
	sawFrames.emplace_back(2.0f, sawUp);
	sawFrames.emplace_back(3.0f, glm::vec3(0, sawDownY, 0));
	for (GLfloat i = 3.25f; i < 5.0f; ++i)
	{
		sawFrames.emplace_back(i, glm::vec3(sawLeftX, sawDownY - 0.25f, 0));
		sawFrames.emplace_back(i + 0.5f, glm::vec3(sawRightX, sawDownY - 0.75f, 0));
		sawDownY -= 0.75f;
	}
	sawFrames.emplace_back(5.0f, glm::vec3(0, sawDownY, 0));
	sawFrames.emplace_back(6.0f, sawUp);
}

void Scene::animate(){
	std::vector<AnimationState> keyframes;
	Model* a[] = { saw, halvedLog, log1, log2 };
	AnimationState state1, state2;
	GLfloat param;
	for (auto it = std::begin(a); it != std::end(a); ++it)
	{
		keyframes = animation[*it];
		for (auto it2 = keyframes.begin(); it2 != keyframes.end(); ++it2)
		{
			if (it2->time > timePosition) {
				state2 = *it2;
				state1 = *(it2 - 1);
				param = (timePosition - state1.time) / (state2.time - state1.time);
				(*it)->setPosition(glm::mix(state1.position, state2.position, param));
				break;
			}
		}
	}
}

void Scene::initModels() {
	// halved log
    CompositeModel* halvedLog = new CompositeModel{};
	this->halvedLog = (Model*)halvedLog;
    CompositeModel* logModel1 = createLog();
    CompositeModel* logModel2 = createLog();
    halvedLog->addModel(logModel1);
    halvedLog->addModel(logModel2);
    ModelComponent &log1 = (*halvedLog)[0], &log2 = (*halvedLog)[1];
	this->log1 =(Model*) &log1;
	this->log2 = (Model*) &log2;
    log1.setPosition(glm::vec3(0,0,0.5f*LOG_WIDTH));
    log2.setPosition(glm::vec3(0,0,-0.5f*LOG_WIDTH));
    halvedLog->setPosition(glm::vec3(0,LOG_Y,HALVED_LOG_Z));
    models.push_back(halvedLog);
	
	// trak
    CompositeModel* trak = new CompositeModel{};
    trak->addMesh(PrimitiveFactory::createSaw(SAW_WIDTH,SAW_DEPTH,32, SAW_COLOR), glm::vec3(0,SAW_Y,0));
    ModelComponent &saw = (*trak)[0];
	this->saw = (Model*)&saw;
    saw.setTexture(blank);
    trak->addMesh(PrimitiveFactory::createBox(TABLE_WIDTH,TABLE_HEIGHT,TABLE_DEPTH, TABLE_COLOR), glm::vec3(0,TABLE_Y,0));
    ModelComponent &table = (*trak)[1];
    table.setTexture(archWood);
    trak->addMesh(PrimitiveFactory::createBox(PILLAR_DEPTH,PILLAR_HEIGHT,PILLAR_DEPTH, PILLAR_COLOR), glm::vec3(PILLAR_DISTANCE,PILLAR_Y,0));
    trak->addMesh(PrimitiveFactory::createBox(PILLAR_DEPTH,PILLAR_HEIGHT,PILLAR_DEPTH, PILLAR_COLOR), glm::vec3(-PILLAR_DISTANCE,PILLAR_Y,0));
    ModelComponent &pillar1 = (*trak)[2], &pillar2 = (*trak)[3];
    pillar1.setTexture(archWood);
    pillar2.setTexture(archWood);
    trak->addMesh(PrimitiveFactory::createPlane(TABLE_WIDTH*BELT_THICKNESS,TABLE_DEPTH, BELT_COLOR), glm::vec3(0,TABLE_HEIGHT + 0.01f,0));
    ModelComponent& belt = (*trak)[4];
    belt.setTexture(blank);
    belt.setQuatRotation(glm::vec3(1,0,0),-glm::half_pi<float>());
    models.push_back(trak);
    
	// ground
	SimpleModel* ground = new SimpleModel(PrimitiveFactory::createPlane(GROUND_SIZE,GROUND_SIZE, GROUND_COLOR));
	ground->setQuatRotation(glm::vec3(1, 0, 0), -glm::half_pi<float>());
    ground->setTexture(groundForest);
    models.push_back(ground);
	
	// log pile
    CompositeModel* logPile = new CompositeModel{};
    for(int i = 0; i < 3; ++i)
    {
        CompositeModel* log = createLog();
        logPile->addModel(log);
        (*logPile)[i].setPosition(glm::vec3((i-1)*2*LOG_RADIUS,0,0));
        (*logPile)[i].setTexture(treeTrunk);
    }
    for(int i = 3; i < 5; ++i)
    {
        CompositeModel* log = createLog();
        logPile->addModel(log);
        (*logPile)[i].setPosition(glm::vec3((2*i-7)*LOG_RADIUS,LOG_RADIUS*2-0.06f,0));
        (*logPile)[i].setTexture(treeTrunk);
    }
    logPile->setPosition(glm::vec3(0,LOG_RADIUS,PILE_Z));
    models.push_back(logPile);
    

	// lamp
    CompositeModel* lamp = new CompositeModel{};
    lamp->addMesh(PrimitiveFactory::createBox(LAMP_POST_THICKNESS,LAMP_POST_HEIGHT,LAMP_POST_THICKNESS, LAMP_POST_COLOR), glm::vec3(0,LAMP_POST_HEIGHT*0.5,0));
    ModelComponent& lampPost = (*lamp)[0];
    lampPost.setTexture(blank);
	lamp->addMesh(PrimitiveFactory::createCylinder(LAMP_RADIUS, LAMP_THICKNESS, CYLINDER_SEGMENTS, LAMP_POST_COLOR), glm::vec3(0,0,0));
	ModelComponent& lampStem = (*lamp)[1];
    lampStem.setTexture(blank);
    lampStem.setPosition(glm::vec3((LAMP_THICKNESS - LAMP_POST_THICKNESS)*0.5,LAMP_POST_HEIGHT+LAMP_RADIUS,0));
	lampStem.setQuatRotation(glm::vec3(0, 1, 0), glm::half_pi<float>());
    lamp->setPosition(glm::vec3(-12.0f - TABLE_WIDTH*0.5f,0,-5));
    models.push_back(lamp);

	light = new Light(lampStem.getFixedPosition() + glm::vec3(LAMP_THICKNESS*0.5f - 0.1f,-LAMP_RADIUS-0.5f,0), LIGHT_COLOR, LIGHT_INTENSITY);
}

void Scene::incrementTime(GLfloat delta) {
	timePosition += delta;
	timePosition = (float)fmod(timePosition, SCENE_CYCLE);
}

void Scene::render(Render renderer) {
	animate();
	renderer.renderLight(*light);
    for(auto it = models.begin(); it != models.end(); ++it) {
        renderer.renderModel(*(*it));
    }
}

Scene::~Scene() {
    for(auto it = models.begin(); it != models.end(); ++it) {
        delete *it;
    }
	delete light;
}
