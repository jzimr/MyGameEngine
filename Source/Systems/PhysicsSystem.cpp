#include "stdafx.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::update(float dt)
{
	Transform* transform;
	Physics* physics;
	Movement* movement;

	Collision collision;


	for (auto& entity : entities)
	{
		transform = entity.second.get()->transformComp;
		physics = entity.second.get()->physicsComp;
		movement = entity.second.get()->movementComp;

		//	Temporary physics system
		if (physics)
		{
			///	Do physics
			physics->velocity.y += physics->gravity * dt;
			physics->velocity.x = physics->horizontalVelocity;

			//	Limit the falling speed
			if (physics->velocity.y >= physics->maxFallingSpeed)
				physics->velocity.y = physics->maxFallingSpeed;

			//	Move entity
			transform->transform.move(physics->velocity * dt);
		}
	}
}

////////////////////////////////////////////////////////////
/// Handle events between systems
///	
////////////////////////////////////////////////////////////

void PhysicsSystem::onNotify(int entity, Event event)
{
	Physics* physics = NULL;
	Movement* movement = NULL;

	//	Find the entity
	auto found = entities.find(entity);
	if (found != entities.end())
	{
		physics = found->second.get()->physicsComp;
		movement = found->second.get()->movementComp;
	}
	else
	{
		std::cout << "Entity not found in notification system (Physics)\n";
		return;
	}

	switch (event)
	{
	case Event::COLLISION_BOTTOM:	//	CollisionSystem
		if (physics->velocity.y > 0)
			physics->velocity.y = 0;
		break;
	case Event::COLLISION_RIGHT:	//	CollisionSystem
		if (physics->velocity.x > 0)
			physics->velocity.x = 0;
		break;
	case Event::COLLISION_LEFT:		//	CollisionSystem
		if (physics->velocity.x < 0)
			physics->velocity.x = 0;
		break;
	case Event::COLLISION_TOP:		//	CollisionSystem
		if (physics->velocity.y < 0)
			physics->velocity.y = 0;
		break;
	case Event::COLLISION_FAULT:	//	CollisionSystem
		break;

	case Event::ENTITY_JUMP:		//	ControllerSystem
		physics->velocity.y = movement->jumpForce * -1;
		break;
	case Event::ENTITY_LEFT:		//	ControllerSystem
		physics->horizontalVelocity -= movement->horizontalSpeed;
		break;
	case Event::ENTITY_RIGHT:		//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_LEFT:	//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_RIGHT:	//	ControllerSystem
		physics->horizontalVelocity -= movement->horizontalSpeed;
	}
}

////////////////////////////////////////////////////////////
/// Methods for physics stuff
///	
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// END
///	
////////////////////////////////////////////////////////////

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