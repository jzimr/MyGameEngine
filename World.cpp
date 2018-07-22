#include "stdafx.h"
#include "World.h"

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

	sf::Texture texture = textureHolder.get("Raptor");
	std::unique_ptr<Entity> scenePtr(new Player());

	scenePtr.get()->addComponent<Sprite2D>();
	scenePtr.get()->getComponent<Sprite2D>().addTexture(texture);

	scenePtr->setPosition(400.f, 50.f);
	mSceneLayers[Front]->attachChild(std::move(scenePtr));
}