#include "stdafx.h"
#include "Game.h"
#include "Constants.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
using namespace Settings;

Game::Game()		//	640, 360
	: mWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "My game :D", sf::Style::Close)
	, mWorld()
	, mFont()
	, mFrameRate()
	, mStatistics()
	, mFrameRateUpdateTime()
	, mFrameRateNumFrames(0)
	, m_systemManager{ new SystemManager(mWindow) }
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
	std::queue<sf::Event> eventQueue;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();

		//	Handled by ControllerSystem
		eventQueue.push(event);
		//	Event flow:
		//	Game -> (Input) -> ControllerSystem -> (Command) -> Entity
	}
	m_systemManager->getSystem<ControllerSystem>().handleInput(eventQueue);
}

void Game::update(sf::Time elapsedTime)
{
	m_systemManager->update(elapsedTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	m_systemManager->getSystem<RenderSystem>().draw(mWindow);

	//	Temporary	(DOES NOT WORK FOR RELEASE MODE FOR SOME REASON D:)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
		sf::Vector2f worldPos = mWindow.mapPixelToCoords(pixelPos, mWindow.getView());
		mStatistics.setString("\n\nMouse position = x: " +
			std::to_string(worldPos.x) + ", y: " + std::to_string(worldPos.y));
	}

	sf::View saveView = mWindow.getView();			//	Save our custom view
	mWindow.setView(mWindow.getDefaultView());		//	This is for some reason necessary in order for sf::Text to work (statistics)

	mWindow.draw(mFrameRate);
	mWindow.draw(mStatistics);

	mWindow.setView(saveView);						//	Set back to our custom view
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
