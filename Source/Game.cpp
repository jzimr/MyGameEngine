#include "stdafx.h"
#include "Game.h"
#include "Constants.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
using namespace Settings;

Game::Game()		//	640, 360
	: mWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Input", sf::Style::Close)
	, mWorld(mWindow)
	//, mPlayer()
	, mFont()
	, mFrameRate()
	, mStatistics()
	, mFrameRateUpdateTime()
	, mFrameRateNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFont.loadFromFile("Media/Sansation.ttf");
	mFrameRate.setFont(mFont);
	mFrameRate.setPosition(5.f, 5.f);
	mFrameRate.setCharacterSize(10);
	
	//mStatistics = mFrameRate;
	mStatistics.setFont(mFont);
	mStatistics.setPosition(5.f, 6.f);
	mStatistics.setCharacterSize(10);
}

void Game::run()
{
	//std::cout << "hi";
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

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

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();

		//	Handled by ControllerSystem
		mWorld.getEventQueue().push(event);
		//	Event flow:
		//	Game -> (Input) -> World -> ControllerSystem -> (Command) -> Entity
	}
	mWorld.handleInput();
}

void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	//	Temporary
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
		sf::Vector2f worldPos = mWindow.mapPixelToCoords(pixelPos, mWindow.getView());
		mStatistics.setString("\n\nMouse position = x: " +
			std::to_string(worldPos.x) + ", y: " + std::to_string(worldPos.y));
	}

	sf::View view = mWindow.getDefaultView();
	mWindow.setView(view);

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
	if (mFrameRateUpdateTime >= sf::seconds(0.1f))
	{
		//sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
		//sf::Vector2f worldPos = mWindow.mapPixelToCoords(pixelPos, mWindow.getView());
		//mStatistics.setString("\n\nMouse position = x: " + 
		//	std::to_string(worldPos.x) + ", y: " + std::to_string(worldPos.y));
	}
}
