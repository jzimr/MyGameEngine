#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "World.h"
#include "Components/Commands/Command.h"

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
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;

	std::queue<std::unique_ptr<Command*>>	commands;
};

#endif // BOOK_GAME_HPP
