#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "World.h"

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
	//Player					mPlayer;

	sf::Font				mFont;
	sf::Text				mFrameRate;
	sf::Text				mStatistics;
	sf::Time				mFrameRateUpdateTime;
	std::size_t				mFrameRateNumFrames;

	//std::queue<std::unique_ptr<Command*>>	commands;
};

#endif // BOOK_GAME_HPP
