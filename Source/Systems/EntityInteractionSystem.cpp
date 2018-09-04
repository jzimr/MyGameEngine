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
	if (action->m_action != action->ENTITY_GRAB)	return;

	std::shared_ptr<Entity> entity = action->m_entity;

	//	If entity is currently not holding any object
	if (!entity->getComponent<LivingThing>().holdingGrabbableObject)
	{
		//	Get all entities that are grabbable
		std::vector<EntPtr> grabbableEntities = entMan.getEntWithComp<Grabbable>();

		//	Create the bounding box for our m_entity
		sf::Vector2f entPos = entity->getPosition();
		sf::FloatRect entBoundaries = entity->getComponent<Anim>().activeAnim.getGlobalBounds();
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
				entity->attachChild(grabEntity, entity);
				entity->getComponent<LivingThing>().holdingGrabbableObject = grabEntity;
			}
		}
	}
	//	Else throw object
	else
	{
		LivingThing* lThing = &entity->getComponent<LivingThing>();
		EntPtr temp = lThing->holdingGrabbableObject;
		lThing->holdingGrabbableObject = NULL;
		action->m_entity->detachChild(temp);
	}
}
