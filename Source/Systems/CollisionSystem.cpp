#include "stdafx.h"
#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

////////////////////////////////////////////////////////////
/// OPTIMIZATION IDEAS:
///	- Implement Grid Collision Checks for optimization.
///	- If velocity is too high and FPS too low, it might skip the collision detection
////////////////////////////////////////////////////////////

void CollisionSystem::update(float dt)
{
	Transform* transform;
	Collider* collider;

	Event collision;

	for (auto& entity : entities)
	{
		transform = entity.second.get()->transformComp;
		collider = entity.second.get()->colliderComp;

		//	Update collider box position from the physicsSystem
		collider->colliderBox.left = transform->transform.getPosition().x;
		collider->colliderBox.top = transform->transform.getPosition().y;

		sf::Vector2f fixPos(0, 0);	//	In case of overlap (Look further down)
		sf::Rect<float> thisRect = collider->colliderBox;
		sf::Rect<float> otherRect;

		for (auto& otherEntity : entities)
		{
			otherRect = otherEntity.second.get()->colliderComp->colliderBox;

			//	Check if otherEntity intersects and is not this entity
			if (thisRect.intersects(otherRect) && entity != otherEntity)
			{
				collision = checkCollision(thisRect, otherRect);

				switch (collision)
				{
				case Event::COLLISION_BOTTOM:
					fixPos = sf::Vector2f(thisRect.left, otherRect.top - thisRect.height);
					break;
				case Event::COLLISION_RIGHT:
					fixPos = sf::Vector2f(otherRect.left - thisRect.width, thisRect.top);
					break;
				case Event::COLLISION_LEFT:
					fixPos = sf::Vector2f(otherRect.left + otherRect.width, thisRect.top);
					break;
				case Event::COLLISION_TOP:
					fixPos = sf::Vector2f(thisRect.left, otherRect.top + otherRect.height);
					break;
				case Event::COLLISION_FAULT:
					break;
				}
				notify(entity.first, collision);	//	Notify all observers about the collision

				transform->transform.setPosition(fixPos);
				collider->colliderBox.left = transform->transform.getPosition().x;
				collider->colliderBox.top = transform->transform.getPosition().y;
			}
		}
	}
}

Event CollisionSystem::checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const
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

	//	Collision beneath main object
	if (t_collision < b_collision && t_collision < l_collision /*+ 1*/ && t_collision < r_collision /*- 1*/)
	{
		return Event::COLLISION_BOTTOM;
	}
	// Collision over main object
	else if (b_collision < t_collision && b_collision < l_collision /*+ 1*/ && b_collision < r_collision /*- 1*/)
	{
		return Event::COLLISION_TOP;
	}
	//	Collision to the right of main object
	else if (l_collision < r_collision && l_collision < t_collision /*+ 1*/ && l_collision < b_collision /*- 1*/)
	{
		return Event::COLLISION_RIGHT;
	}
	//	Collision to the left of main object
	else if (r_collision < l_collision && r_collision < t_collision /*+ 1*/ && r_collision < b_collision /*- 1*/)
	{
		return Event::COLLISION_LEFT;
	}
	//	If nothing collided after all (Probably because of corner of otherEntity)
	else
	{
		return Event::COLLISION_FAULT;
	}
}

void CollisionSystem::onEntityUpdate(const Entity * entity)
{
	int entityID = entity->getID();
	bool hasRequirements = entity->hasComponent<Transform>() &&
		entity->hasComponent<Collider>();
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
		Collider* playerColl = entity->hasComponent<Collider>() ?
			&entity->getComponent<Collider>() : NULL;

		std::unique_ptr<EntComponents> newInsert{ new EntComponents(playerTrans, playerColl) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

																					//	Found in our list		=	Calibrate component adress (just in case)
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}
