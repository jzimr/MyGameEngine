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
	events.subscribe<MoveToPos>(this, &PhysicsSystem::receiveT);	//	Maybe move into own System?
}

void PhysicsSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Transform, Physics>();

	Transform* globalTransform;
	Physics* physics;
	Movement* movement;


	for (auto& entity : entities)
	{
		MoveToPos moveToPos(entity);
		globalTransform = &entity->getComponent<Transform>();
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
			moveToPos.m_newEntPos = globalTransform->globalTransform.getPosition() + (physics->velocity * dt);
			events.emit<MoveToPos>(moveToPos);
			//transform->transform.move(physics->velocity * dt);		MIGHT THIS SIMPLY BE BETTER?
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

//	TEMPORARY SOLUTION (NEEDS ALOT OF IMPORVEMENT)
//	TODO: Implement localmovement with globalmovement
//	TODO: Find better way to handle movement of children
void PhysicsSystem::receiveT(MoveToPos* moveToPos)
{
	Transform* transform = &moveToPos->m_entity->getComponent<Transform>();
	Parentable* parentable = moveToPos->m_entity->hasComponent<Parentable>() ?
		&moveToPos->m_entity->getComponent<Parentable>() : NULL;

	sf::Vector2f distMoved = moveToPos->m_newEntPos - transform->globalTransform.getPosition();

	transform->globalTransform.move(distMoved);

	if (parentable)		//	Then we have to move the children as well
	{
		for (auto& child : parentable->children)
		{
			Transform* childTransform = &child->getComponent<Transform>();

			childTransform->globalTransform.move(distMoved);
		}
	}
}