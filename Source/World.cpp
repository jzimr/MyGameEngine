#include "stdafx.h"
#include "Entity.h"
#include "Systems/SystemManager.h"
#include "Entity Factories/EntityFactory.h"
#include "Terrain.h"

World::World(sf::RenderWindow& window)
	: mWindow{ window }
	//, mSceneGraph{}
	//, mSceneLayers{}
	, textureHolder{}
	, uniqueEntID{ 0 }
	, systemManager{ new SystemManager(/*window*/) }
	, factory{ this }
{
	loadTextures();
	buildScene();
}

Entity* World::addEntity(std::string entityName, sf::Vector2f position)
{
	std::unique_ptr<Entity> newEntity = factory.spawnEntity(entityName, getUniqueID(), position);
	entities.push_back(std::move(newEntity));	//	Add to list
	Entity* entPtr = entities.back().get();

	//	Notify the system about changes
	systemManager->notify(entPtr, SystemEvent::ENTITY_UPDATE);

	return entPtr;
}

void World::entityUpdated()
{

}

int World::getUniqueID()
{
	return uniqueEntID++;
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
	terrain->draw(mWindow);
}

sf::Texture World::getTexture(std::string name) const
{
	return textureHolder.get(name);
}

std::queue<sf::Event>& World::getEventQueue()
{
	return eventQueue;
}

void World::loadTextures()
{
	textureHolder.load("Raptor", "Media/Textures/Raptor.png");
	textureHolder.load("Ground", "Media/Textures/Ground.png");
	textureHolder.load("Wood", "Media/Textures/Wood.png");
	textureHolder.load("RedPixel", "Media/Textures/RedPixel.png");
	textureHolder.load("Grass", "Media/Textures/Grass.png");
	textureHolder.load("Dirt", "Media/Textures/Dirt.png");
	textureHolder.load("Player", "Media/Textures/Player.png");
}

void World::buildScene()
{
	terrain = new Terrain(1, this);
	terrain->createChunk();

	player = addEntity("Player", sf::Vector2f(216, 250));
	Entity* ground = addEntity("Ground", sf::Vector2f(0, 400));
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