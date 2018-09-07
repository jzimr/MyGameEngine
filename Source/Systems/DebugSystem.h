#pragma once
#include "Systems/System.h"
#include <queue>
#include <mutex>
#include <thread>

class DebugSystem : public System
{
public:
	DebugSystem();

	//bool checkForWrongSyntax(int args, int minArgs, int maxArgs);
	void fetchCommands();			//	On a seperate thread so the user can write into console
	void processCommands();			//	On main thread, that processes and executes the m_commands in queue

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

private:
	EntityManager entMan;

	std::mutex m_allCommMtx;
	std::queue<std::vector<std::string>> m_commands;		//	Queue with list of m_commands consisting of words

	std::thread commandLineThread;

	//FetchCommands comms;			//	Run on a seperate thread
};

//class FetchCommands			//	This class is supposed to run on a seperate thread
//{
//	FetchCommands(std::mutex& allCommMtx, std::queue<std::vector<std::string>>& commands);
//};