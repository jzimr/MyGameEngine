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
	EntPtr ground = entMan.createEntity("Ground", sf::Vector2f(0, 400));
	EntPtr ground2 = entMan.createEntity("Ground", sf::Vector2f(200, 350));
	entMan.createEntity("Block", sf::Vector2f(250, 330));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	entMan.createEntity("Block", sf::Vector2f(250, 300));
	
	//for (int i = 0; i < 60; i++)
	//{
	//	entMan.createEntity("Block", sf::Vector2f(250 + i * 3, 300 + i * 3));
	//}
}