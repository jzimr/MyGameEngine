// MyGame123.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <thread>
#include <Windows.h>

int main(int argc, char *argv[])
{
	//std::thread t1(task1);

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

