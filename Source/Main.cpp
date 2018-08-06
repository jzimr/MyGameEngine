// MyGame123.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

//	For testing
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "Entity Factories/EntityFactory.h"

int main()
{
	//EntityFactory factory(NULL);

	//factory.spawnEntity("Player", 20);

	//factory.spawnEntity("hi");

	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}

