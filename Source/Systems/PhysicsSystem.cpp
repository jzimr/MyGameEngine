#include "stdafx.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::update(float dt)
{
	Transform* transform;
	Physics* physics;
	Collider* collider;
	Movement* movement;

	for (auto& entity : entities)
	{
		transform = entity.second.get()->transformComp;
		physics = entity.second.get()->physicsComp;
		collider = entity.second.get()->colliderComp;
		movement = entity.second.get()->movementComp;

		//	Temporary physics system (Will fail if velocity i too high)
		if (physics)
		{
			///	Do physics
			physics->velocity.y += physics->gravity * dt;

			//	Check for max falling speed
			if (physics->velocity.y >= physics->maxFallingSpeed)
				physics->velocity.y = physics->maxFallingSpeed;
			
			///	Do movement
			if (movement)
			{

			}

			/// Do collision (Must be done at end of all components)
			if (collider)
			{
				//	Check collision on ground
				if (checkCollision(*entity.second.get(), entity.first) && physics->velocity.y > 0)
					physics->velocity.y = 0;
			}

			///	Apply all transformations
			//	Move entity
			transform->transform.move(physics->velocity * dt);
			//	Move collider
			if (collider)
			{
				collider->colliderBox.left = transform->transform.getPosition().x;
				collider->colliderBox.top = transform->transform.getPosition().y;
			}
		}
	}
}

////////////////////////////////////////////////////////////
/// Handle events between systems
///	
////////////////////////////////////////////////////////////

void PhysicsSystem::onNotify(int entity, Event event)
{
	Physics* physicsComp = NULL;
	Movement* movementComp = NULL;

	//	Find the entity
	auto found = entities.find(entity);
	if (found != entities.end())
	{
		physicsComp = found->second.get()->physicsComp;
		movementComp = found->second.get()->movementComp;
	}

	switch (event)
	{
	case Event::ENTITY_JUMP:		//	ControllerSystem
		physicsComp->velocity.y = movementComp->jumpForce * -1;
		break;
	case Event::ENTITY_LEFT:		//	ControllerSystem
		physicsComp->velocity.x = -1 * movementComp->horizontalSpeed;
		break;
	case Event::ENTITY_RIGHT:		//	ControllerSystem
		physicsComp->velocity.x = movementComp->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_LEFT:
		physicsComp->velocity.x += movementComp->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_RIGHT:
		physicsComp->velocity.x -= movementComp->horizontalSpeed;
	}
}

////////////////////////////////////////////////////////////
/// Methods to perform physics stuff
///	
////////////////////////////////////////////////////////////

void PhysicsSystem::addForce(Physics& physicsComp, sf::Vector2f velocity)
{
	physicsComp.velocity += velocity;
}

bool PhysicsSystem::checkCollision(const EntComponents& entity, int ID) const
{
	sf::Rect<float>* collider = &entity.colliderComp->colliderBox;
	float left = collider->left, top = collider->top,
		width = collider->width, height = collider->height;

	sf::Rect<float>* otherCollider;
	float oLeft, oTop, oWidth, oHeight;

	for (auto& ent : entities)
	{
		//	If otherEntity doesn't have collider component or is thisEntity
		if (!ent.second.get()->colliderComp || ent.first == ID)
			continue;

		otherCollider = &ent.second.get()->colliderComp->colliderBox;
		oLeft = otherCollider->left, oTop = otherCollider->top,
			oWidth = otherCollider->width, oHeight = otherCollider->height;

		//std::cout << left << ", " << top << " | " << width << ", " << height
		//	<< "   ||||||   " << oLeft << ", " << oTop << " | " << oWidth << ", " << oHeight
		//	<< '\n';

		//	Collision ontop of an object
		if (top + height >= oTop && (left + width >= oLeft && left <= oLeft + oWidth))
			return true;
		//	Collision infront of an object


		//	Collision over an object

	}
	return false;
}


void PhysicsSystem::onEntityUpdate(const Entity* entity)
{
	int entityID = entity->getID();
	bool hasRequirements = entity->hasComponent<Transform>() &&
		(entity->hasComponent<Physics>() || entity->hasComponent<Collider>()
			|| entity->hasComponent<Movement>());
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
		Transform* playerTrans = &entity->getComponent<Transform>();
		Physics* playerPhys = entity->hasComponent<Physics>() ?
			&entity->getComponent<Physics>() : NULL;
		Collider* playerColl = entity->hasComponent<Collider>() ?
			&entity->getComponent<Collider>() : NULL;
		Movement* playerMove = entity->hasComponent<Movement>() ?
			&entity->getComponent<Movement>() : NULL;

		std::unique_ptr<EntComponents> newInsert{ new EntComponents(playerTrans, playerPhys, playerColl, playerMove) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

		//	Found in our list		=	Calibrate component adress (just in case)
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}