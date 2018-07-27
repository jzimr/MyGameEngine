#include "stdafx.h"
#include "World.h"
#include "Components/Sprite2D.h"
#include "Components/Physics/Physics.h"
#include "Components/Controller.h"

World::World(sf::RenderWindow& window)
	: mWindow{ window }
	, mSceneGraph{}
	, mSceneLayers{}
	, textureHolder{}
{
	loadTextures();
	buildScene();
}

void World::update(float dt)
{
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	textureHolder.load("Raptor", "Media/Textures/Raptor.png");
}

void World::buildScene()
{
	for (int i = 0; i < Layer::LayerSize; i++)
	{
		Entity::EntPtr layer(new Entity());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	//	Read all entities from file
		//	If entity.component contains Controller component
		//	player = entity;
	

	//sf::Texture texture = textureHolder.get("Raptor");
	//std::unique_ptr<Entity> player(new Entity());

	//player.get()->addComponent<Sprite2D>();
	//player.get()->getComponent<Sprite2D>().addTexture(texture);

	//player.get()->addComponent<Physics>();
	//player.get()->addComponent<Controller>();

	//player->setPosition(400.f, 50.f);
	//mSceneLayers[Front]->attachChild(std::move(player));
}