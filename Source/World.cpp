#include "stdafx.h"
#include "Entity.h"
#include "World.h"
#include "Systems/SystemManager.h"
#include "Entity Factories/EntityFactory.h"
#include "SFML/System/Time.hpp"

World::World(sf::RenderWindow& window)
	: mWindow{ window }
	, entMan{}
	//, mSceneGraph{}
	//, mSceneLayers{}
	//, textureHolder{}
	, uniqueEntID{ 0 }
	//, factory{ this }
	, systemManager{ new SystemManager(/*window*/) }
{
	//loadTextures();
	buildScene();
	//systemManager->update(0);
}

//Entity* World::addEntity(std::string entityName, sf::Vector2f position)
//{
//	std::unique_ptr<Entity> newEntity = factory.spawnEntity(entityName, getUniqueID(), position);
//	entities.push_back(std::move(newEntity));	//	Add to list
//	Entity* entPtr = entities.back().get();
//
//	//	Notify the system about changes
//	systemManager->notify(entPtr, SystemEvent::ENTITY_UPDATE);
//
//	return entPtr;
//}

void World::entityUpdated()
{

}

//int World::getUniqueID()
//{
//	return uniqueEntID++;
//}

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

//void World::loadTextures()
//{
//	textureHolder.load("Raptor", "Media/Textures/Raptor.png");
//	textureHolder.load("Ground", "Media/Textures/Ground.png");
//	textureHolder.load("Wood", "Media/Textures/Wood.png");
//	textureHolder.load("RedPixel", "Media/Textures/RedPixel.png");
//	textureHolder.load("Player", "Media/Textures/Player.png");
//}

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