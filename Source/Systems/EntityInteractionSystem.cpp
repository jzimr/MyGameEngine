#include "stdafx.h"
#include "EntityInteractionSystem.h"

typedef Action::EntAction EntAction;
using namespace SystemBehaviourSettings;

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
	Entity* entity = action->m_entity;

	//	If entity is currently not holding any object
	if (!entity->getComponent<LivingThing>().holdingGrabbableObject)
	{
		//	Get all entities that are grabbable
		std::vector<Entity*> grabbableEntities = entMan.getEntWithComp<Grabbable>();

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

			if (abs(grabEntBoundaries.left - (entBoundaries.left + entBoundaries.width)) <= GRABBABLE_DISTANCE)
			{
				sf::Vector2f holdingPosition = sf::Vector2f(entBoundaries.width + 1, entBoundaries.height / 2 - 2);
				entity->attachChild(grabEntity, holdingPosition);			//	Temp offset
				entity->getComponent<LivingThing>().holdingGrabbableObject = grabEntity;
				
				if (grabEntity->hasComponent<Physics>())								//	Temp
					grabEntity->removeComponent<Physics>();								//	Temp

				return;	
			}
		}
	}
	//	Else throw object
	else
	{
		LivingThing* lThing = &entity->getComponent<LivingThing>();
		Entity* temp = lThing->holdingGrabbableObject;
		lThing->holdingGrabbableObject = NULL;
		Entity* droppedObj = action->m_entity->detachChild(temp);

		//	Temp throwing
		&droppedObj->addComponent<Physics>();
		Physics* childPhys = &droppedObj->getComponent<Physics>();
		Physics* parentPhys = &entity->getComponent<Physics>();

		int direction = 1;
		if (droppedObj->getLocalPosition().x < 0)
			direction *= -1;

		childPhys->force = sf::Vector2f((200 + abs(parentPhys->velocity.x)) * direction, 0);
	}
}
