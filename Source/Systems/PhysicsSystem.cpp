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

	for (auto& entity : entities)
	{
		transform = entity.second.get()->transformComp;
		physics = entity.second.get()->physicsComp;
		collider = entity.second.get()->colliderComp;

		//	Apply gravity
		if (physics)
		{
			physics->velocity.y += physics->gravity * dt;

			if (collider)
			{
				if (checkCollision(*entity.second.get(), entity.first))
				{
					physics->velocity.y = 0;
				}
				//	Update collider position
			}

			//	Apply all transformations calculated
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
/// Methods to perform physics stuff
///	
////////////////////////////////////////////////////////////

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
		if (top + height >= oTop && (left + width >= oLeft || left <= oLeft + width))
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
		(entity->hasComponent<Physics>() || entity->hasComponent<Collider>());
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
		Collider* PlayerColl = entity->hasComponent<Collider>() ?
			&entity->getComponent<Collider>() : NULL;

		std::unique_ptr<EntComponents> newInsert{ new EntComponents(playerTrans, playerPhys, PlayerColl) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

		//	Found in our list		=	Calibrate component adress (just in case)
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}