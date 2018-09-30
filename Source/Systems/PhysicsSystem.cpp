#include "stdafx.h"
#include "PhysicsSystem.h"
#include "MathHelperFunctions.h"
#include "SystemBehaviourSettings.h"

typedef Collision::CollisionDirection CollisionDirection;
typedef Action::EntAction EntAction;
using namespace HelperFuncs;
using namespace SystemBehaviourSettings;

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
		physics = &m_entity->getComponent<Physics>();
		movement = m_entity->hasComponent<Movement>() ? &m_entity->getComponent<Movement>() : NULL;

		if (physics)
		{
			///	Do physics
			if(physics->velocity.x != 0 || physics->velocity.y != 0)	//	To prevent 0/1 problem
				addForce(physics, -1.0f * physics->velocity * FRICTION * physics->mass / getLength(physics->velocity));

			//sf::Vector2f acc = physics->force * physics->mass;
			/*physics->velocity += acc * dt;*/
			physics->velocity += physics->force * (dt / physics->mass);		// a = F/m

			if(abs(physics->velocity.x) >= physics->maxSpeed)
				physics->velocity.x = physics->velocity.x < 0 ? -1 * physics->maxSpeed : physics->maxSpeed;
			if (abs(physics->velocity.y) >= physics->maxSpeed)
				physics->velocity.y = physics->velocity.y < 0 ? -1 * physics->maxSpeed : physics->maxSpeed;

			// Checks for if velocity is legal
			/*if (abs(physics->velocity.y) > physics->maxSpeed)
				physics->velocity.y = physics->velocity.y < 0 ? -1 * physics->maxSpeed : physics->maxSpeed;
			if (abs(physics->velocity.x) > physics->maxSpeed)
				physics->velocity.x = physics->velocity.x < 0 ? -1 * physics->maxSpeed : physics->maxSpeed;*/

				//	move entity
			m_entity->move(physics->velocity * dt);		//	Simplectic Euler integration

			// reset
			physics->force = sf::Vector2f(0, 0);
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
	Entity* entity = collision->m_entity;
	Entity* otherEntity = collision->m_other_entity;

	//		TEMP	//
	//	Set the new position of both the children AND the parents if collision has happened
	sf::Vector2f newPosDist = collision->m_newEntPos - collision->m_entity->getPosition();

	physics = collision->m_entity->hasComponent<Physics>() ? &collision->m_entity->getComponent<Physics>() : NULL;

	while (entity->hasParent() && physics == NULL)
	{
		entity = entity->getParent();
		physics = entity->hasComponent<Physics>() ? &entity->getComponent<Physics>() : NULL;
	}

	entity->move(newPosDist);		//	Update from top-down in hierachy

	if (!otherEntity || !otherEntity->hasComponent<Physics>())	//	If object is static
	{
		///	Remove velocities on collision direction
		switch (collision->m_direction)
		{
		case CollisionDirection::COLLISION_BOTTOM:	//	CollisionSystem
			if (physics->velocity.y > 0)
			{
				physics->velocity.y = 0;
				physics->force = sf::Vector2f(0, 0);		//	TEMP
			}
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
	else
	{
		doElasticCollision(entity, otherEntity);
	}
}

void PhysicsSystem::receiveA(Action* action)
{
	if (!action->m_entity->hasComponent<Physics>())
		return;

	Physics* physics = &action->m_entity->getComponent<Physics>();
	Movement* movement = &action->m_entity->getComponent<Movement>();

	switch (action->m_action)
	{

	case EntAction::ENTITY_UP:			//	ControllerSystem
		addForce(physics, sf::Vector2f(0, -1 * movement->mSpeed));
		break;
	case EntAction::ENTITY_DOWN:		//	ControllerSystem
		addForce(physics, sf::Vector2f(0, movement->mSpeed));
		break;
	case EntAction::ENTITY_LEFT:		//	ControllerSystem
		addForce(physics, sf::Vector2f(-1 * movement->mSpeed, 0));
		for (auto child : action->m_entity->getChildren())
			if (child->getLocalPosition().x > 0)
				child->setLocalPosition(child->getLocalPosition().x * (-1), child->getLocalPosition().y);
		break;
	case EntAction::ENTITY_RIGHT:		//	ControllerSystem
		addForce(physics, sf::Vector2f(movement->mSpeed, 0));
		for (auto child : action->m_entity->getChildren())
			if (child->getLocalPosition().x < 0)
				child->setLocalPosition(child->getLocalPosition().x * (-1), child->getLocalPosition().y);
		break;
		//case EntAction::STOP_ENTITY_UP:	//	ControllerSystem
		//	addForce(physics, sf::Vector2f(0, movement->mSpeed));
		//	break;
		//case EntAction::STOP_ENTITY_DOWN:	//	ControllerSystem
		//	addForce(physics, sf::Vector2f(0, -1 * movement->mSpeed));
		//	break;
		//case EntAction::STOP_ENTITY_LEFT:	//	ControllerSystem
		//	addForce(physics, sf::Vector2f(movement->mSpeed, 0));
		//	break;
		//case EntAction::STOP_ENTITY_RIGHT:	//	ControllerSystem
		//	addForce(physics, sf::Vector2f(-1 * movement->mSpeed, 0));
		//	break;
	}
}

void PhysicsSystem::addForce(Physics* physics, const sf::Vector2f nForce)
{
	physics->force += nForce;
}

void PhysicsSystem::doElasticCollision(Entity* a, Entity* b)
{
	Physics* aPhys = &a->getComponent<Physics>(),
		*bPhys = &b->getComponent<Physics>();

	sf::Vector2f aVel = aPhys->velocity, bVel = bPhys->velocity,	// Velocity a, b
		aDir = normalize(aVel), bDir = normalize(bVel);					// Normalized velocity a, b
	float aMass = aPhys->mass, bMass = bPhys->mass;

	///	(1) Find directions of tangent |et| and normal |en|
	sf::Vector2f en = normalize(a->getPosition() - b->getPosition());
	sf::Vector2f et = sf::Vector2f(-en.x, en.y);

	/// (2) Express u1 and u2 in terms of en and et -> ui = (vi * en)*en + (vi * et)*et
	float v1en = multiplyVectors(aVel, en);
	float v1et = multiplyVectors(aVel, et);
	float v2en = multiplyVectors(bVel, en);
	float v2et = multiplyVectors(bVel, et);

	///	(3) Do 1D-collision in the direction en
	float v1 = ((aMass - bMass) * v1en + 2 * bMass * v2en) / (aMass + bMass);
	float v2 = ((bMass - aMass) * v2en + 2 * aMass * v1en) / (aMass + bMass);

	/// (4) Add up new velocity in the direction en with old velocity in direction et
	sf::Vector2f aNewVel = scaleVector(v1, en) + scaleVector(v1et, et);
	sf::Vector2f bNewVel = scaleVector(v2, en) + scaleVector(v2et, et);
	//sf::Vector2f aNewVel = scaleVector(v2en, en) + scaleVector(v1et, et);
	//sf::Vector2f bNewVel = scaleVector(v1en, en) + scaleVector(v2et, et);

	aPhys->velocity = aNewVel;
	bPhys->velocity = bNewVel;
}

