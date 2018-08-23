#include "stdafx.h"
#include "ControllerSystem.h"

ControllerSystem::ControllerSystem()
{
}

void ControllerSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Controller>();
}

void ControllerSystem::handleInput(std::queue<sf::Event>& events)
{
	sf::Event event;
	while (!events.empty())
	{
		event = events.front();

		for (auto& entity : entities)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
					notify(entity->getID(), EventID::ENTITY_JUMP);
				else if (event.key.code == sf::Keyboard::A)
					notify(entity->getID(), EventID::ENTITY_LEFT);
				else if (event.key.code == sf::Keyboard::D)
					notify(entity->getID(), EventID::ENTITY_RIGHT);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::A)
					notify(entity->getID(), EventID::STOP_ENTITY_LEFT);
				else if (event.key.code == sf::Keyboard::D)
					notify(entity->getID(), EventID::STOP_ENTITY_RIGHT);
			}
		}
		events.pop();		//	Remove event from queue
	}
}