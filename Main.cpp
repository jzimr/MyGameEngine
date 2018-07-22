// MyGame123.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

//	For testing
#include "BaseProperty.h"
#include "Property.h"
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "Health.h"
#include "Test.h"


int main()
{
	Entity ent;

	ent.addComponent<Test>();
	ent.addComponent<Health>();
	ent.getComponent<Test>().getTest();

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

