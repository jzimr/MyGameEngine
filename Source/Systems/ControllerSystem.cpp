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

	sf::Event event;

	while (!m_eventQueue->empty())
	{
		event = m_eventQueue->front();

		for (auto& m_entity : entities)
		{
			Action entAction(m_entity);

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
					entAction.m_action = EntAction::ENTITY_JUMP;
				else if (event.key.code == sf::Keyboard::A)
					entAction.m_action = EntAction::ENTITY_LEFT;
				else if (event.key.code == sf::Keyboard::D)
					entAction.m_action = EntAction::ENTITY_RIGHT;
				else if (event.key.code == sf::Keyboard::E)
					entAction.m_action = EntAction::ENTITY_GRAB;

			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::A)
					entAction.m_action = EntAction::STOP_ENTITY_LEFT;
				else if (event.key.code == sf::Keyboard::D)
					entAction.m_action = EntAction::STOP_ENTITY_RIGHT;
			}

			events.emit<Action>(entAction);
		}
		m_eventQueue->pop();		//	Remove event from queue
	}
}

//	Spaghetti?
void ControllerSystem::handleInput(std::queue<sf::Event>& events)
{
	m_eventQueue = &events;		//	Copy the queue to this system so we can use it in update()
}