#include "stdafx.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

////////////////////////////////////////////////////////////
/// OPTIMIZATION IDEAS:
///	- Implement Grid Collision Checks for optimization.
////////////////////////////////////////////////////////////

void PhysicsSystem::update(float dt)
{
	Transform* transform;
	Physics* physics;
	Collider* collider;
	Movement* movement;

	Collision collision;


	for (auto& entity : entities)
	{
		transform = entity.second.get()->transformComp;
		physics = entity.second.get()->physicsComp;
		collider = entity.second.get()->colliderComp;
		movement = entity.second.get()->movementComp;

		//	Temporary physics system (Will fail if velocity is too high)
		if (physics)
		{
			///	Do physics
			physics->velocity += physics->gravity * dt;
			//if(physics->velocity.x < 0.9999999 && physics->velocity.x > -0.9999999)
			physics->velocity.x = physics->horizontalVelocity;

			//	Check for max falling speed
			if (physics->velocity.y >= physics->maxFallingSpeed)
				physics->velocity.y = physics->maxFallingSpeed;

			/// Do collision (Must be done at end of all components)
			//	TODO: put the intersection code into own function
			sf::Vector2f fixPos(0, 0);	//	In case of overlap (Look further down)
			if (collider)
			{
				sf::Rect<float> thisRect = collider->colliderBox;
				sf::Rect<float> otherRect;

				for (auto& otherEntity : entities)
				{
					otherRect = otherEntity.second.get()->colliderComp->colliderBox;
					otherRect.left += 1; otherRect.top += 1; otherRect.width -= 1; otherRect.height -= 1;

					//	Check if otherEntity intersects and is not this entity
					if (thisRect.intersects(otherRect) && entity != otherEntity)
					{
						collision = checkCollision(thisRect, otherRect, physics->velocity);

						switch (collision)
						{
						case COLLISION_BOTTOM:
							fixPos = sf::Vector2f(thisRect.left, otherRect.top - thisRect.height);
							if (physics->velocity.y > 0)
								physics->velocity.y = 0;
							break;
						case COLLISION_RIGHT:
							fixPos = sf::Vector2f(otherRect.left - thisRect.width, thisRect.top);
							if (physics->velocity.x > 0)
								physics->velocity.x = 0;
							break;
						case COLLISION_LEFT:
							fixPos = sf::Vector2f(otherRect.left + otherRect.width/* + 1*/, thisRect.top);
							if (physics->velocity.x < 0)
								physics->velocity.x = 0;
							break;
						case COLLISION_TOP:
							fixPos = sf::Vector2f(thisRect.left, otherRect.top + otherRect.height/* + 1*/);
							if (physics->velocity.y < 0)
								physics->velocity.y = 0;
							break;
						case COLLISION_FAULT:
							break;
						}
						transform->transform.setPosition(fixPos);
						//std::cout << transform->transform.getPosition().x << ", "
							//<< transform->transform.getPosition().y << '\n';
					}
				}
			}

			///	Apply all transformations
			//	Move entity
			transform->transform.move(physics->velocity * dt);
			
			//std::cout << collider->colliderBox.height << '\n';
		}
		//	Move collider	( Update in case static blocks have been moved as well)
		if (collider)
		{
			collider->colliderBox.left = transform->transform.getPosition().x;
			collider->colliderBox.top = transform->transform.getPosition().y;
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
		physicsComp->horizontalVelocity -= movementComp->horizontalSpeed;
		break;
	case Event::ENTITY_RIGHT:		//	ControllerSystem
		physicsComp->horizontalVelocity += movementComp->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_LEFT:
		physicsComp->horizontalVelocity += movementComp->horizontalSpeed;
		break;
	case Event::STOP_ENTITY_RIGHT:
		physicsComp->horizontalVelocity -= movementComp->horizontalSpeed;
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

PhysicsSystem::Collision PhysicsSystem::checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect,
	const sf::Vector2f velocity) const
{
	float left = rect.left, top = rect.top,
		width = rect.width, height = rect.height;

	float oLeft = otherRect.left, oTop = otherRect.top,
		oWidth = otherRect.width, oHeight = oHeight = otherRect.height;

	float this_bottom = top + height;
	float other_bottom = oTop + oHeight;
	float this_right = left + width;
	float other_right = oLeft + oWidth;

	float b_collision = other_bottom - top;
	float t_collision = this_bottom - oTop;
	float l_collision = this_right - oLeft;
	float r_collision = other_right - left;

	//std::cout << left << ", " << top << " | " << width << ", " << height
	//	<< "   ||||||   " << oLeft << ", " << oTop << " | " << oWidth << ", " << oHeight
	//	<< '\n';

	///	Check for collisions
	//	Faults with this method:
		//	- If velocity too high, it might go into other collider
		//	- If FPS too low, it might go into the other collider
		//	- If inside other collider, player is stuck
		//	- If hitting the side of another collider, the collision detection goes bongos

		//	Collision beneath main object
	if (t_collision < b_collision && t_collision < l_collision + 1 && t_collision < r_collision - 1)
	{
		return COLLISION_BOTTOM;
	}
	// Collision over main object
	else if (b_collision < t_collision && b_collision < l_collision + 1 && b_collision < r_collision - 1)
	{
		return COLLISION_TOP;
	}
	//	Collision to the right of main object
	else if (l_collision < r_collision && l_collision < t_collision + 1 && l_collision < b_collision - 1)
	{
		return COLLISION_RIGHT;
	}
	//	Collision to the left of main object
	else if (r_collision < l_collision && r_collision < t_collision + 1 && r_collision < b_collision - 1)
	{
		return COLLISION_LEFT;
	}
	//	If nothing collided after all (Probably because of corner of otherEntity)
	else
	{
		std::cout << "lawl\n";
		return COLLISION_FAULT;
	}
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