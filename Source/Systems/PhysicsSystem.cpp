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
	entities = entMan.getEntWithComp<Physics>();

	Physics* physics;
	Movement* movement;


	for (auto& m_entity : entities)
	{
		//MoveToPos moveToPos(m_entity);
		physics = &m_entity->getComponent<Physics>();
		movement = m_entity->hasComponent<Movement>() ? &m_entity->getComponent<Movement>() : NULL;

		if (physics)
		{
			///	Do physics
			physics->velocity.y += physics->gravity * dt;
			physics->velocity.x = physics->horizontalVelocity;

			//	Limit the falling speed
			if (physics->velocity.y >= physics->maxFallingSpeed)
				physics->velocity.y = physics->maxFallingSpeed;

			//std::cout << physics->velocity.y * dt << '\n';

			m_entity->move(physics->velocity * dt);
		}
	}
}

////////////////////////////////////////////////////////////
/// Handle events between systems
///	
////////////////////////////////////////////////////////////

void PhysicsSystem::receiveC(Collision* collision)
{
	Physics* physics = NULL;
	std::shared_ptr<Entity> entity;

	//		TEMP	//
	//	Set the new position of both the children AND the parents if collision has happened
	sf::Vector2f newPosDist = collision->m_newEntPos - collision->m_entity->getPosition();
	entity = collision->m_entity;

	physics = collision->m_entity->hasComponent<Physics>() ? &collision->m_entity->getComponent<Physics>() : NULL;

	while (entity->hasParent() && physics == NULL)
	{
		entity = entity->getParent();
		physics = entity->hasComponent<Physics>() ? &entity->getComponent<Physics>() : NULL;
	}

	entity->move(newPosDist);		//	Update from top-down in hierachy

	///	Remove velocities on collision direction
	switch (collision->m_direction)
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