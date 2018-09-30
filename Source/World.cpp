#include "stdafx.h"
#include "World.h"

World::World()
	: entMan{}
{
	buildScene();
}

void World::buildScene()
{
	player = entMan.createEntity("Player", sf::Vector2f(216, 250));
	player->getComponent<Physics>().mass = 1.0f;
	player->getComponent<Movement>().mSpeed = 500.0f;
	//player->attachChild(entMan.createEntity("Spear"), sf::Vector2f(20, 10));
	Entity* ground = entMan.createEntity("Ground", sf::Vector2f(0, 400));
	Entity* ground2 = entMan.createEntity("Ground", sf::Vector2f(200, 350));

	Entity* block = entMan.createEntity("Block", sf::Vector2f(250, 330));
	block->getComponent<Physics>().mass = 2.f;


	//for (int i = 0; i < 60; i++)
	//{
	//	entMan.createEntity("Block", sf::Vector2f(250 + i * 3, 300 + i * 3));
	//}
}