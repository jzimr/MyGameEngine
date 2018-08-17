#include "stdafx.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::update(float dt)
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
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entity)
		{
			physics = &entities[i]->getComponent<Physics>();
			movement = &entities[i]->getComponent<Movement>();
		}
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