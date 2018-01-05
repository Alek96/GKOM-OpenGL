#include <cmath>
#include <iterator>
#include <glm/gtc/quaternion.hpp>
#include "../Texture/texture.h"
#include "../Model/PrimitiveFactory.h"
#include "scene.h"

void Scene::setPositionTexture(ModelComponent* model, glm::vec3 position, Texture texture) {
	model->setPosition(position);
	model->setTexture(texture);
}

ModelComposite* Scene::createLog() {
	ModelComposite* log = new ModelComposite;

	ModelComponent* cylinder = new ModelComponent(PrimitiveFactory::createCylinder(LOG_RADIUS, LOG_WIDTH, CYLINDER_SEGMENTS, TRUNK_COLOR));
	setPositionTexture(cylinder, glm::vec3(0.0f, 0.0f, 0.0f), treeTrunk);
	log->add(cylinder);

	ModelComponent* circle1 = new ModelComponent(PrimitiveFactory::createCircle(LOG_INSIDE_RADIUS, CYLINDER_SEGMENTS, TRUNK_INSIDE_COLOR));
	setPositionTexture(circle1, glm::vec3(0, 0, -LOG_WIDTH * 0.5f - 0.01f), treeStump);
	log->add(circle1);

	ModelComponent* circle2 = new ModelComponent(PrimitiveFactory::createCircle(LOG_INSIDE_RADIUS, CYLINDER_SEGMENTS, TRUNK_INSIDE_COLOR));
	setPositionTexture(circle2, glm::vec3(0, 0, LOG_WIDTH*0.5f + 0.01f), treeStump);
	log->add(circle2);

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
	log2Frames.emplace_back(10.4f, glm::vec3(0, -0.65f*logSpeed, -0.5f*LOG_WIDTH + 1.4f*logSpeed));/**/

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
	sawFrames.emplace_back(6.0f, sawUp);/**/
}

void Scene::animate(){
	std::vector<AnimationState> keyframes;
	//Model* a[] = { halvedLog };
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
	{
		ModelComposite* halvedLog = new ModelComposite;
		halvedLog->add(createLog());
		halvedLog->add(createLog());
		(*halvedLog)[0]->setPosition(glm::vec3(0, 0, 0.5f*LOG_WIDTH));
		(*halvedLog)[1]->setPosition(glm::vec3(0, 0, -0.5f*LOG_WIDTH));
		halvedLog->setPosition(glm::vec3(0, LOG_Y, HALVED_LOG_Z));
		this->halvedLog = halvedLog;
		this->log1 = (*halvedLog)[0];
		this->log2 = (*halvedLog)[1];
		models.add(halvedLog);
	}
	// trak
	{
		ModelComposite* trak = new ModelComposite{};

		ModelComponent* saw = new ModelComponent(PrimitiveFactory::createSaw(SAW_WIDTH, SAW_DEPTH, 32, SAW_COLOR));
		setPositionTexture(saw, glm::vec3(0, SAW_Y, 0), blank);
		this->saw = saw;
		trak->add(saw);

		ModelComponent* table = new ModelComponent(PrimitiveFactory::createBox(TABLE_WIDTH, TABLE_HEIGHT, TABLE_DEPTH, TABLE_COLOR));
		setPositionTexture(table, glm::vec3(0, TABLE_Y, 0), archWood);
		trak->add(table);

		ModelComponent* pilar1 = new ModelComponent(PrimitiveFactory::createBox(PILLAR_DEPTH, PILLAR_HEIGHT, PILLAR_DEPTH, PILLAR_COLOR));
		setPositionTexture(pilar1, glm::vec3(PILLAR_DISTANCE, PILLAR_Y, 0), archWood);
		trak->add(pilar1);

		ModelComponent* pilar2 = new ModelComponent(PrimitiveFactory::createBox(PILLAR_DEPTH, PILLAR_HEIGHT, PILLAR_DEPTH, PILLAR_COLOR));
		setPositionTexture(pilar2, glm::vec3(-PILLAR_DISTANCE, PILLAR_Y, 0), archWood);
		trak->add(pilar2);

		ModelComponent* belt = new ModelComponent(PrimitiveFactory::createPlane(TABLE_WIDTH*BELT_THICKNESS, TABLE_DEPTH, BELT_COLOR));
		setPositionTexture(belt, glm::vec3(0, TABLE_HEIGHT + 0.01f, 0), blank);
		belt->setQuatRotation(glm::vec3(1, 0, 0), -glm::half_pi<float>());
		trak->add(belt);

		models.add(trak);
	}

	// ground
	{
		ModelComponent* ground = new ModelComponent(PrimitiveFactory::createPlane(GROUND_SIZE, GROUND_SIZE, GROUND_COLOR));
		ground->setQuatRotation(glm::vec3(1, 0, 0), -glm::half_pi<float>());
		ground->setTexture(groundForest);
		models.add(ground);
	}

	// log pile
	{
		ModelComposite* logPile = new ModelComposite{};

		for (int i = 0; i < 3; ++i)
		{
			ModelComposite* log = createLog();
			log->setPosition(glm::vec3((i - 1) * 2 * LOG_RADIUS, 0, 0));
			logPile->add(log);
		}
		for (int i = 3; i < 5; ++i)
		{
			ModelComposite* log = createLog();
			log->setPosition(glm::vec3((2 * i - 7)*LOG_RADIUS, LOG_RADIUS * 2 - 0.06f, 0));
			logPile->add(log);
		}
		logPile->setPosition(glm::vec3(0, LOG_RADIUS, PILE_Z));
		models.add(logPile);
	}

	// lamp
	{
		ModelComposite* lamp = new ModelComposite{};

		ModelComponent* lampPost = new ModelComponent(PrimitiveFactory::createBox(LAMP_POST_THICKNESS, LAMP_POST_HEIGHT, LAMP_POST_THICKNESS, LAMP_POST_COLOR));
		setPositionTexture(lampPost, glm::vec3(0, LAMP_POST_HEIGHT*0.5, 0), blank);
		lamp->add(lampPost);

		ModelComponent* lampStem = new ModelComponent(PrimitiveFactory::createCylinder(LAMP_RADIUS, LAMP_THICKNESS, CYLINDER_SEGMENTS, LAMP_POST_COLOR));
		setPositionTexture(lampStem, glm::vec3((LAMP_THICKNESS - LAMP_POST_THICKNESS)*0.5, LAMP_POST_HEIGHT + LAMP_RADIUS, 0), blank);
		lampStem->setQuatRotation(glm::vec3(0, 1, 0), glm::half_pi<float>());
		lamp->add(lampStem);

		lamp->setPosition(glm::vec3(-12.0f - TABLE_WIDTH * 0.5f, 0, -5));
		models.add(lamp);

		light = new Light(lampStem->getPosition() + glm::vec3(LAMP_THICKNESS*0.5f - 0.1f, -LAMP_RADIUS - 0.5f, 0), LIGHT_COLOR, LIGHT_INTENSITY);
	}
}

void Scene::incrementTime(GLfloat delta) {
	timePosition += delta;
	timePosition = (float)fmod(timePosition, SCENE_CYCLE);
}

void Scene::render(Render renderer) {
	animate();
	renderer.renderLight(*light);
    renderer.renderModel(&models);
}

Scene::~Scene() {
	delete light;
}
