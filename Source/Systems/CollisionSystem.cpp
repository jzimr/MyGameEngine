#include "stdafx.h"
#include "CollisionSystem.h"
#include <memory>
#include "Events.h"

//typedef Collision::CollisionDirection CollisionDirection;

CollisionSystem::CollisionSystem()
	: entMan{}
{
}

void CollisionSystem::configure(EventManager& events)
{
	events.subscribe<Message>(this, &CollisionSystem::receive);
}

////////////////////////////////////////////////////////////
/// OPTIMIZATION IDEAS:
///	- Implement Grid Collision Checks for optimization.
///	- If velocity is too high and FPS too low, it might skip the collision detection
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/// OPTIMIZATION TODO:
///	1. Implement basic vertical slicing. Grids of e.g. 10 blocks width
///	2. Further improve by creating a quadtree for collisionchecking (See bookmarked link):
///		https://gamedev.stackexchange.com/questions/10202/quad-trees-grid-based-collision-putting-logic-into-action
////////////////////////////////////////////////////////////

void CollisionSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Collider>();

	Collider* collider;			//	Required
	Physics* physics;			//	Not required

	CollisionDirection collisionDir;

	for (auto& m_entity : entities)
	{
		if (m_entity->hasComponent<Player>())
			playerComp = &m_entity->getComponent<Player>();

		//MoveToPos moveToPos(m_entity);
		collider = &m_entity->getComponent<Collider>();
		physics = m_entity->hasComponent<Physics>() ? &m_entity->getComponent<Physics>() : NULL;

		if (!physics)	//	Only make exception to check for collision if parent has physics
		{
			//	Check if the parent of this entity has the Physics component. If yes, check for collision
			if (!m_entity->hasParent())
				continue;
			else
			{
				std::shared_ptr<Entity> currEnt = m_entity;
				bool parentHasPhysics = false;

				while (currEnt != NULL)
				{
					if (currEnt->hasComponent<Physics>())
					{
						parentHasPhysics = true;
						break;
					}
					currEnt = currEnt->getParent();
				}
				if (!parentHasPhysics)
					continue;
			}
		}

		//	Update collider box position from the physicsSystem
		collider->colliderBox.left = m_entity->getPosition().x;
		collider->colliderBox.top = m_entity->getPosition().y;

		sf::Vector2f fixPos(0, 0);	//	In case of overlap (Look further down)
		sf::Rect<float>* thisRect = &collider->colliderBox;
		sf::Rect<float> otherRect;

		//	For each m_entity collider
		for (auto& otherEntity : entities)
		{
			otherRect = otherEntity->getComponent<Collider>().colliderBox;

			//	Check if otherEntity intersects and is not this m_entity
			if (thisRect->intersects(otherRect) && m_entity != otherEntity && !m_entity->isRelatedWith(otherEntity))
			{
				collisionDir = checkCollision(*thisRect, otherRect);			//	Get collision m_direction
				fixPos = fixPositionOnCollide(collisionDir, *thisRect, otherRect);		//	Fix position when colliding

				Collision collision(collisionDir, fixPos, m_entity, &otherEntity->getComponent<Collider>());
				events.emit<Collision>(collision);

				collider->colliderBox.left = m_entity->getPosition().x;
				collider->colliderBox.top = m_entity->getPosition().y;
			}
		}

		//	For each  terrain collider
		for (auto& terrainCollider : terrainColliders)
		{
			otherRect = terrainCollider.colliderBox;

			//	Check if otherEntity intersects and is not this m_entity
			if (thisRect->intersects(otherRect))
			{
				collisionDir = checkCollision(*thisRect, otherRect);			//	Get collision m_direction
				fixPos = fixPositionOnCollide(collisionDir, *thisRect, otherRect);		//	Fix position when colliding

				Collision collision(collisionDir, fixPos, m_entity, &terrainCollider);
				events.emit<Collision>(collision);

				collider->colliderBox.left = m_entity->getPosition().x;
				collider->colliderBox.top = m_entity->getPosition().y;
			}
		}
	}
}

void CollisionSystem::updateChunks()
{
	terrainColliders.clear();			//	Clear list (Implement a more effective way without needing to delete all chunks)

	for (const auto& chunkElem : playerComp->loadedChunks)
	{
		Chunk* chunk = chunkElem.get();
		Collider collider;
		collider.colliderBox = sf::FloatRect(0, 0, 0, 0);

		std::vector<sf::Sprite>::iterator it = chunk->topBlocks.begin();

		while (it != chunk->topBlocks.end())
		{
			//	Set startposition of collider to the first sprite
			if (collider.colliderBox == sf::FloatRect(0, 0, 0, 0))
			{
				collider.colliderBox = it->getGlobalBounds();
				++it;
			}

			//	Block is part of collider
			else if (it->getGlobalBounds().top == collider.colliderBox.top)
			{
				collider.colliderBox.width += it->getGlobalBounds().width;
				++it;
			}

			//	End of collider
			else
			{
				terrainColliders.push_back(collider);
				collider.colliderBox = sf::FloatRect(0, 0, 0, 0);
			}
		}

		terrainColliders.push_back(collider);		//	For the last cluster
	}
}


void CollisionSystem::receive(Message* message)
{
	if (*message == Message::CHUNK_UPDATE)
	{
		updateChunks();
	}
}

CollisionDirection CollisionSystem::checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect)
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
		return CollisionDirection::COLLISION_BOTTOM;
	}
	// Collision over main object
	else if (b_collision < t_collision && b_collision < l_collision /*+ 1*/ && b_collision < r_collision /*- 1*/)
	{
		return CollisionDirection::COLLISION_TOP;
	}
	//	Collision to the right of main object
	else if (l_collision < r_collision && l_collision < t_collision /*+ 1*/ && l_collision < b_collision /*- 1*/)
	{
		return CollisionDirection::COLLISION_RIGHT;
	}
	//	Collision to the left of main object
	else if (r_collision < l_collision && r_collision < t_collision /*+ 1*/ && r_collision < b_collision /*- 1*/)
	{
		return CollisionDirection::COLLISION_LEFT;
	}
	//	If nothing collided after all
	else
	{
		return CollisionDirection::COLLISION_FAULT;
	}
}

sf::Vector2f CollisionSystem::fixPositionOnCollide(CollisionDirection collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect)
{
	switch (collDirection)
	{
	case CollisionDirection::COLLISION_BOTTOM:
		return sf::Vector2f(rect.left, otherRect.top - rect.height);
	case CollisionDirection::COLLISION_RIGHT:
		return sf::Vector2f(otherRect.left - rect.width, rect.top);
	case CollisionDirection::COLLISION_LEFT:
		return sf::Vector2f(otherRect.left + otherRect.width, rect.top);
	case CollisionDirection::COLLISION_TOP:
		return sf::Vector2f(rect.left, otherRect.top + otherRect.height);
	default:
		return sf::Vector2f(rect.left, rect.top);
	}
}