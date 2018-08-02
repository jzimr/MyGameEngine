#include "stdafx.h"
#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "Input", sf::Style::Close)
	, mWorld(mWindow)
	//, mPlayer()
	, mFont()
	, mFrameRate()
	, mFrameRateUpdateTime()
	, mFrameRateNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFont.loadFromFile("Media/Sansation.ttf");
	mFrameRate.setFont(mFont);
	mFrameRate.setPosition(5.f, 5.f);
	mFrameRate.setCharacterSize(10);
	mStatistics = mFrameRate;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			///		ADD MORE SYSTEMS (Physics, collision, etc.)

			processInput();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processInput()
{
	sf::Event event;
	//std::queue<sf::Event> eventQueue;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
		///		Temporary solution to input handling
	}
}

void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mFrameRate);
	mWindow.draw(mStatistics);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mFrameRateUpdateTime += elapsedTime;
	mFrameRateNumFrames += 1;

	if (mFrameRateUpdateTime >= sf::seconds(1.0f))
	{
		mFrameRate.setString(
			"Frames / Second = " + std::to_string(mFrameRateNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mFrameRateUpdateTime.asMicroseconds() / mFrameRateNumFrames) + "us\n");

		mFrameRateUpdateTime -= sf::seconds(1.0f);
		mFrameRateNumFrames = 0;
	}
	if(mFrameRateUpdateTime >= sf::seconds(0.1f))
		mStatistics.setString("\n\nMouse position = x: " + std::to_string(sf::Mouse::getPosition(mWindow).x) + ", y: " + std::to_string(sf::Mouse::getPosition(mWindow).y));
}
