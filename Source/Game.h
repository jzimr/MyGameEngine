#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "World.h"
#include "Systems/SystemManager.h"		//	If circular dependency error, probably this is the cause

#include <queue>

class Game : private sf::NonCopyable
{
public:
	Game();
	void					run();


private:
	void					processInput();
	void					update(sf::Time elapsedTime);
	void					render();
	void					updateStatistics(sf::Time elapsedTime);


private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	World					mWorld;

	sf::Font				mFont;
	sf::Text				mFrameRate;
	sf::Text				mStatistics;
	sf::Time				mFrameRateUpdateTime;
	std::size_t				mFrameRateNumFrames;

	SystemManager*			m_systemManager;				//	Handles all systems
};

#endif
