#include "stdafx.h"
#include "ControllerSystem.h"

ControllerSystem::ControllerSystem()
{
}

void ControllerSystem::update(float dt)
{
}

void ControllerSystem::handleInput(std::queue<sf::Event>& events)
{
	//std::cout << "yo";
	sf::Event event;
	while (!events.empty())
	{
		event = events.front();

		for (auto& entity : entities)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
					notify(entity.first, Event::ENTITY_JUMP);
				else if (event.key.code == sf::Keyboard::A)
					notify(entity.first, Event::ENTITY_LEFT);
				else if (event.key.code == sf::Keyboard::D)
					notify(entity.first, Event::ENTITY_RIGHT);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::A)
					notify(entity.first, Event::STOP_ENTITY_LEFT);
				else if (event.key.code == sf::Keyboard::D)
					notify(entity.first, Event::STOP_ENTITY_RIGHT);
			}
		}
		events.pop();		//	Remove event from queue
	}
}

void ControllerSystem::onEntityUpdate(const Entity* entity)
{
	int entityID = entity->getID();
	bool hasRequirements = entity->hasComponent<Controller>();
	auto foundInMap = entities.find(entityID);

	//	False in entity
	if (!hasRequirements)
	{
		//	Not found in our list	=	No action
		if (foundInMap == entities.end())
			return;

		//	Found in our list		=	Remove from list
		else if (foundInMap != entities.end())
			entities.erase(entityID);
	}
	//	True in Entity
	else if (hasRequirements)
	{
		Controller* entityContr = &entity->getComponent<Controller>();

		std::unique_ptr<EntComponents> newInsert{ new EntComponents(entityContr) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

		//	Found in our list		=	Calibrate component adress (just in case)
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}