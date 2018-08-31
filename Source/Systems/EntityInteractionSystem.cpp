#include "stdafx.h"
#include "EntityInteractionSystem.h"

typedef Action::EntAction EntAction;

EntityInteractionSystem::EntityInteractionSystem()
{

}

void EntityInteractionSystem::configure(EventManager& events)
{
	events.subscribe<Action>(this, &EntityInteractionSystem::receiver);
}

void EntityInteractionSystem::update(float dt, EventManager& events)
{
	//entities = entMan.getEntWithComps<Grabbable>();
}

void EntityInteractionSystem::receiver(Action* action)
{
	switch (action->m_action)
	{
	case EntAction::ENTITY_GRAB:
		handleGrabbing(action);
	}
}
void EntityInteractionSystem::handleGrabbing(Action* action)
{
	//	Get all entities that are grabbable
	std::vector<EntPtr> grabbableEntities = entMan.getEntWithComp<Grabbable>();
	
	//	Create the bounding box for our m_entity
	sf::Vector2f entPos = action->m_entity->getPosition();
	sf::FloatRect entBoundaries = action->m_entity->getComponent<Anim>().activeAnim.getGlobalBounds();
	entBoundaries.left = entPos.x; entBoundaries.top = entPos.y;

	//	Create the bounding box for the grabbable object
	sf::Vector2f grabEntPos;
	sf::FloatRect grabEntBoundaries;

	for (const auto& grabEntity : grabbableEntities)
	{
		grabEntPos = grabEntity->getPosition();
		grabEntBoundaries = grabEntity->getComponent<Sprite2D>().sprite.getGlobalBounds();
		grabEntBoundaries.left = grabEntPos.x; grabEntBoundaries.top = grabEntPos.y;

		if (grabEntBoundaries.left - (entBoundaries.left + entBoundaries.width) <= GrabbableDistance)
		{
			action->m_entity->attachChild(grabEntity);
		}
	}
}
