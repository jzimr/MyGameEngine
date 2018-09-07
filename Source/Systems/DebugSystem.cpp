#include "stdafx.h"
#include "DebugSystem.h"

using namespace std::placeholders;

DebugSystem::DebugSystem()
	: m_commands{}
{
}

void DebugSystem::fetchCommands()
{
	std::string input;

	while (input != "exit")
	{
		std::cout << "Command: ";
		std::getline(std::cin, input);		//	Wait and read for command

		std::istringstream iss(input);
		std::vector<std::string> words{		//	Split command
			std::istream_iterator<std::string>(iss),{}
		};
		if (words.empty())					//	Blank line detected, skip
			continue;

		while (true)						//	Foolproof access to queue
			if (m_allCommMtx.try_lock())
			{
				m_commands.push(words);
				m_allCommMtx.unlock();
				break;
			}
	}
}

void DebugSystem::processCommands()
{
	while (!m_commands.empty())
	{
		std::vector<std::string> command;
		while (true)
			if (m_allCommMtx.try_lock())
			{
				command = m_commands.front();		//	Get front
				m_commands.pop();					//	Remove from queue
				m_allCommMtx.unlock();
				break;
			}

		//////////////////////////////////////////////
		//	Syntax: spawnEntity [EntName] [x] [y]
		//////////////////////////////////////////////
		if (command[0] == "spawnEntity")
		{
			int xPos, yPos;

			try
			{
				xPos = std::stoi(command[2]);
				yPos = std::stoi(command[3]);
			}
			catch (const std::invalid_argument& ex)
			{
				std::cout << "Invalid Argument: " << ex.what() << '\n';
				continue;
			}

			entMan.createEntity(command[1], sf::Vector2f(xPos, yPos));
		}
	}
}

void DebugSystem::configure(EventManager & events)
{
	commandLineThread = std::thread(&DebugSystem::fetchCommands, this);
}

void DebugSystem::update(float dt, EventManager & events)
{
	if (!m_commands.empty())
		processCommands();
}

//FetchCommands::FetchCommands(std::mutex& allCommMtx, std::queue<std::vector<std::string>>& commands)
//{
//	std::string input;
//
//	while (input != "exit")
//	{
//		std::cout << "Command: ";
//		std::getline(std::cin, input);		//	Wait and read for command
//
//		std::istringstream iss(input);
//		std::vector<std::string> words{		//	Split command
//			std::istream_iterator<std::string>(iss),{}
//		};
//		if (words.empty())					//	Blank line detected, skip
//			continue;
//
//		while (true)						//	Foolproof access to queue
//			if (allCommMtx.try_lock())
//			{
//				commands.push(words);
//				allCommMtx.unlock();
//				break;
//			}
//	}
//}
