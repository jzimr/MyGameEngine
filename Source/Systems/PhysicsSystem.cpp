#include "stdafx.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Transform, Physics>();

	Transform* transform;
	Physics* physics;
	Movement* movement;

	for (auto& entity : entities)
	{
		transform = &entity->getComponent<Transform>();
		physics = &entity->getComponent<Physics>();
		movement = entity->hasComponent<Movement>() ? &entity->getComponent<Movement>() : NULL;

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

void PhysicsSystem::onNotify(int entity, EventID event)
{
	Physics* physics = NULL;
	Movement* movement = NULL;

	//	Find the entity
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entity)
		{
			physics = &entities[i]->getComponent<Physics>();
			if(entities[i]->hasComponent<Movement>())
				movement = &entities[i]->getComponent<Movement>();
			break;
		}
	}

	switch (event)
	{
	case EventID::COLLISION_BOTTOM:	//	CollisionSystem
		if (physics->velocity.y > 0)
			physics->velocity.y = 0;
		break;
	case EventID::COLLISION_RIGHT:	//	CollisionSystem
		if (physics->velocity.x > 0)
			physics->velocity.x = 0;
		break;
	case EventID::COLLISION_LEFT:		//	CollisionSystem
		if (physics->velocity.x < 0)
			physics->velocity.x = 0;
		break;
	case EventID::COLLISION_TOP:		//	CollisionSystem
		if (physics->velocity.y < 0)
			physics->velocity.y = 0;
		break;
	case EventID::COLLISION_FAULT:	//	CollisionSystem
		break;

	case EventID::ENTITY_JUMP:		//	ControllerSystem
		physics->velocity.y = movement->jumpForce * -1;
		break;
	case EventID::ENTITY_LEFT:		//	ControllerSystem
		physics->horizontalVelocity -= movement->horizontalSpeed;
		break;
	case EventID::ENTITY_RIGHT:		//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case EventID::STOP_ENTITY_LEFT:	//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case EventID::STOP_ENTITY_RIGHT:	//	ControllerSystem
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