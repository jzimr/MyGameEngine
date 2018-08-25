#include "stdafx.h"
#include "PhysicsSystem.h"

typedef Collision::CollisionDirection CollisionDirection;
typedef Action::EntAction EntAction;

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::configure(EventManager& events)
{
	events.subscribe<Collision>(this, &PhysicsSystem::receiveC);
	events.subscribe<Action>(this, &PhysicsSystem::receiveA);
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

void PhysicsSystem::receiveC(Collision* collision)
{
	Physics* physics = &collision->entity->getComponent<Physics>();

	switch (collision->direction)
	{
	case CollisionDirection::COLLISION_BOTTOM:	//	CollisionSystem
		if (physics->velocity.y > 0)
			physics->velocity.y = 0;
		break;
	case CollisionDirection::COLLISION_RIGHT:	//	CollisionSystem
		if (physics->velocity.x > 0)
			physics->velocity.x = 0;
		break;
	case CollisionDirection::COLLISION_LEFT:		//	CollisionSystem
		if (physics->velocity.x < 0)
			physics->velocity.x = 0;
		break;
	case CollisionDirection::COLLISION_TOP:		//	CollisionSystem
		if (physics->velocity.y < 0)
			physics->velocity.y = 0;
		break;
	case CollisionDirection::COLLISION_FAULT:	//	CollisionSystem
		break;
	}
}

void PhysicsSystem::receiveA(Action* action)
{
	Physics* physics = &action->m_entity->getComponent<Physics>();
	Movement* movement = &action->m_entity->getComponent<Movement>();

	switch (action->m_action)
	{

	case EntAction::ENTITY_JUMP:		//	ControllerSystem
		physics->velocity.y = movement->jumpForce * -1;
		break;
	case EntAction::ENTITY_LEFT:		//	ControllerSystem
		physics->horizontalVelocity -= movement->horizontalSpeed;
		break;
	case EntAction::ENTITY_RIGHT:		//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case EntAction::STOP_ENTITY_LEFT:	//	ControllerSystem
		physics->horizontalVelocity += movement->horizontalSpeed;
		break;
	case EntAction::STOP_ENTITY_RIGHT:	//	ControllerSystem
		physics->horizontalVelocity -= movement->horizontalSpeed;

	}
}

//void PhysicsSystem::onNotify(int entity, EventID event)
//{
//	Physics* physics = NULL;
//	Movement* movement = NULL;
//
//	//	Find the entity
//	for (size_t i = 0; i < entities.size(); i++)
//	{
//		if (entities[i]->getID() == entity)
//		{
//			physics = &entities[i]->getComponent<Physics>();
//			if (entities[i]->hasComponent<Movement>())
//				movement = &entities[i]->getComponent<Movement>();
//			break;
//		}
//	}
//
//	switch (event)
//	{
//
//	case EntAction::ENTITY_JUMP:		//	ControllerSystem
//		physics->velocity.y = movement->jumpForce * -1;
//		break;
//	case EntAction::ENTITY_LEFT:		//	ControllerSystem
//		physics->horizontalVelocity -= movement->horizontalSpeed;
//		break;
//	case EntAction::ENTITY_RIGHT:		//	ControllerSystem
//		physics->horizontalVelocity += movement->horizontalSpeed;
//		break;
//	case EntAction::STOP_ENTITY_LEFT:	//	ControllerSystem
//		physics->horizontalVelocity += movement->horizontalSpeed;
//		break;
//	case EntAction::STOP_ENTITY_RIGHT:	//	ControllerSystem
//		physics->horizontalVelocity -= movement->horizontalSpeed;
//	}
//}

////////////////////////////////////////////////////////////
/// Methods for physics stuff
///	
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// END
///	
////////////////////////////////////////////////////////////