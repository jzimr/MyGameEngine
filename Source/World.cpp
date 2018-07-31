#include "stdafx.h"
#include "Entity.h"
#include "Components/Sprite2D.h"
#include "Components/Physics/Physics.h"
#include "Components/Controller.h"
#include "Systems/SystemManager.h"

World::World(sf::RenderWindow& window)
	: mWindow{ window }
	//, mSceneGraph{}
	//, mSceneLayers{}
	, textureHolder{}
	, uniqueEntID{ 0 }
	, systemManager{ new SystemManager(/*window*/) }
{
	loadTextures();
	buildScene();
}

void World::createEntity()
{
	std::unique_ptr<Entity> newPlayer(new Entity(uniqueEntID++));

	Transform& transform = newPlayer.get()->addComponent<Transform>();
	newPlayer.get()->getComponent<Transform>().transform.setPosition(200, 200);

	Sprite2D& sprite2D = newPlayer.get()->addComponent<Sprite2D>();
	
	sprite2D.texture = textureHolder.get("Raptor");
	newPlayer.get()->getComponent<Sprite2D>().sprite = sf::Sprite(newPlayer.get()->getComponent<Sprite2D>().texture);

	//	Notify the system about changes
	systemManager->notify(newPlayer.get(), SystemEvent::ENTITY_UPDATE);

	entities.push_back(std::move(newPlayer));
}

void World::update(float dt)
{
	systemManager->update(dt);
	//	Rather update individually in systems
	//mSceneGraph.update(dt);	//	Make systems responsible for update 
}

void World::draw()
{
	//	Temporary
	systemManager->getSystem<RenderSystem>().draw(mWindow);
}

void World::loadTextures()
{
	textureHolder.load("Raptor", "Media/Textures/Raptor.png");
}

void World::buildScene()
{
	createEntity();

	//for (int i = 0; i < Layer::LayerSize; i++)
	//{
	//	Entity::EntPtr layer(new Entity());
	//	mSceneLayers[i] = layer.get();
	//	mSceneGraph.attachChild(std::move(layer));
	//}

	//	Read all entities from file
		//	If entity.component contains Controller component
		//	player = entity;
	//sf::Texture texture = textureHolder.get("Raptor");
	//std::unique_ptr<Entity> player = EntFactory::Player::create(texture);

	//player->setPosition(300, 300);
	//mSceneLayers[Front]->attachChild(std::move(player));
}