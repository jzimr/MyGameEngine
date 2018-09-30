#include "stdafx.h"
#include "ControllerSystem.h"

typedef Action::EntAction EntAction;

ControllerSystem::ControllerSystem()
	: m_eventQueue{}
{
}

void ControllerSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Controller>();

	for (auto& m_entity : entities)
	{
		Action entAction(m_entity);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			entAction.m_action = EntAction::ENTITY_UP;
			events.emit<Action>(entAction);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			entAction.m_action = EntAction::ENTITY_LEFT;
			events.emit<Action>(entAction);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			entAction.m_action = EntAction::ENTITY_DOWN;
			events.emit<Action>(entAction);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			entAction.m_action = EntAction::ENTITY_RIGHT;
			events.emit<Action>(entAction);
		}

		while (!m_eventQueue.empty())
		{
			sf::Event event;
			event = m_eventQueue.front();

			if (event.type == sf::Event::KeyPressed)
			{
				//if (event.key.code == sf::Keyboard::W)
				//	entAction.m_action = EntAction::ENTITY_UP;
				//else if (event.key.code == sf::Keyboard::S)
				//	entAction.m_action = EntAction::ENTITY_DOWN;
				//else if (event.key.code == sf::Keyboard::A)
				//	entAction.m_action = EntAction::ENTITY_LEFT;
				//else if (event.key.code == sf::Keyboard::D)
				//	entAction.m_action = EntAction::ENTITY_RIGHT;
				if (event.key.code == sf::Keyboard::E)
					entAction.m_action = EntAction::ENTITY_GRAB;
				else if (event.key.code == sf::Keyboard::B)
					entAction.m_action = EntAction::ENTITY_BUILD;
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				//if (event.key.code == sf::Keyboard::W)
				//	entAction.m_action = EntAction::STOP_ENTITY_UP;
				//else if (event.key.code == sf::Keyboard::S)
				//	entAction.m_action = EntAction::STOP_ENTITY_DOWN;
				//if (event.key.code == sf::Keyboard::A)
				//	entAction.m_action = EntAction::STOP_ENTITY_LEFT;
				//else if (event.key.code == sf::Keyboard::D)
				//	entAction.m_action = EntAction::STOP_ENTITY_RIGHT;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					entAction.m_action = EntAction::ENTITY_CLICK_LEFT;
			}

			events.emit<Action>(entAction);
			m_eventQueue.pop();		//	Remove event from queue
		}
	}
}

//	Spaghetti?
void ControllerSystem::handleInput(std::queue<sf::Event> events)
{
	m_eventQueue = events;		//	Copy the queue to this system so we can use it in update()
}