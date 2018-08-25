#include "stdafx.h"
#include "Entity.h"
#include "World.h"
#include "Systems/SystemManager.h"

World::World(sf::RenderWindow& window)
	: mWindow{ window }
	, entMan{}
	//, mSceneGraph{}
	//, mSceneLayers{}
	//, textureHolder{}
	, uniqueEntID{ 0 }
	//, factory{ this }
	, systemManager{ new SystemManager() }
{
	//loadTextures();
	buildScene();
	//systemManager->update(0);
}

void World::entityUpdated()
{

}


void World::update(float dt)
{
	systemManager->update(dt);
	//	Rather update individually in systems
	//mSceneGraph.update(dt);	//	Make systems responsible for update 
}

void World::handleInput()	//	From Game.cpp
{
	//	Temporary
	systemManager->getSystem<ControllerSystem>().handleInput(eventQueue);
}

void World::draw()
{
	//	Temporary
	systemManager->getSystem<RenderSystem>().draw(mWindow);
	//	Temporary
	//terrain->draw(mWindow);
}

//sf::Texture World::getTexture(std::string name) const
//{
//	//return textureHolder.get(name);
//}

std::queue<sf::Event>& World::getEventQueue()
{
	return eventQueue;
}

void World::buildScene()
{
	//terrain = new Terrain(1, this);
	//terrain->createChunk();

	player = entMan.createEntity("Player", sf::Vector2f(216, 250));
	EntPtr ground = entMan.createEntity("Ground", sf::Vector2f(0, 400));
	EntPtr ground2 = entMan.createEntity("Ground", sf::Vector2f(200, 350));
	entMan.createEntity("Block", sf::Vector2f(250, 330));

	//std::cout << ground->getComponent<Transform>().transform.getPosition().y << '\n';
	//std::cout << ground2->getComponent<Transform>().transform.getPosition().y << '\n';
	////for(int i = 0; i < 1000; i++)
	//Entity* wood = addEntity("Wood", sf::Vector2f(300, 370));

	//for (int i = 0; i < Layer::LayerSize; i++)
	//{
	//	Entity::EntPtr layer(new Entity());
	//	mSceneLayers[i] = layer.get();
	//	mSceneGraph.attachChild(std::move(layer));
	//}

	//mSceneLayers[Front]->attachChild(std::move(player));
}