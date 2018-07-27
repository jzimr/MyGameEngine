// MyGame123.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

//	For testing
#include "BaseProperty.h"
#include "Property.h"
#include <vector>
#include "Entity.h"
#include "Components\Component.h"
#include "Components\Health.h"
#include "Components\Test.h"


int main()
{
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

