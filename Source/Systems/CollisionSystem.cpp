#include "stdafx.h"
#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
	: entMan{}
{
}

void CollisionSystem::configure(EventManager& events)
{
	events.subscribe<Message>(this, &CollisionSystem::receive);		//	If it doesn't work, change function so you directly
											//	send the function pointer as parameter to EventManager
	//	Read about std::bind
}

////////////////////////////////////////////////////////////
/// OPTIMIZATION IDEAS:
///	- Implement Grid Collision Checks for optimization.
///	- If velocity is too high and FPS too low, it might skip the collision detection
////////////////////////////////////////////////////////////

void CollisionSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComps<Transform, Collider>();

	Transform * transform;		//	Required
	Collider* collider;			//	Required
	Physics* physics;			//	Not required

	EventID collision;

	for (auto& entity : entities)
	{
		if (entity->hasComponent<Player>())
			playerComp = &entity->getComponent<Player>();


		transform = &entity->getComponent<Transform>();
		collider = &entity->getComponent<Collider>();
		physics = entity->hasComponent<Physics>() ? &entity->getComponent<Physics>() : NULL;

		if (!physics)		//	No point in checking for collision on static object
			continue;

		//	Update collider box position from the physicsSystem
		collider->colliderBox.left = transform->transform.getPosition().x;
		collider->colliderBox.top = transform->transform.getPosition().y;

		sf::Vector2f fixPos(0, 0);	//	In case of overlap (Look further down)
		sf::Rect<float>* thisRect = &collider->colliderBox;
		sf::Rect<float> otherRect;

		//	For each entity collider
		for (auto& otherEntity : entities)
		{
			otherRect = otherEntity->getComponent<Collider>().colliderBox;

			//	Check if otherEntity intersects and is not this entity
			if (thisRect->intersects(otherRect) && entity != otherEntity)
			{
				collision = checkCollision(*thisRect, otherRect);			//	Get collision direction
				fixPos = fixPositionOnCollide(collision, *thisRect, otherRect);		//	Fix position when colliding

				notify(entity->getID(), collision);	//	Notify all observers about the collision

				transform->transform.setPosition(fixPos);
				collider->colliderBox.left = transform->transform.getPosition().x;
				collider->colliderBox.top = transform->transform.getPosition().y;
			}
		}

		//	For each  terrain collider
		for (auto& terrainCollider : terrainColliders)
		{
			otherRect = terrainCollider.colliderBox;

			//	Check if otherEntity intersects and is not this entity
			if (thisRect->intersects(otherRect))
			{
				collision = checkCollision(*thisRect, otherRect);			//	Get collision direction
				fixPos = fixPositionOnCollide(collision, *thisRect, otherRect);		//	Fix position when colliding

				notify(entity->getID(), collision);	//	Notify all observers about the collision

				transform->transform.setPosition(fixPos);
				collider->colliderBox.left = transform->transform.getPosition().x;
				collider->colliderBox.top = transform->transform.getPosition().y;

			}
		}
		//std::cout << "collision amount: " << i << '\n';
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

//template<typename T>
//void RegisterEventHandler(const std::string& type, void (T::*handler)(Event*), T* obj)
//{
//	mCallbackList[type].push_back(boost::bind(handler, obj, _1));
//}
//
//template<typename T1, typename T2>
//void RegisterEventHandler(const String& type, T1 handler, T2* obj)
//{
//	void (T2::*evtHandler)(Event*) = (void (T2::*)(Event*)) (handler);
//	mCallbackList[type].push_back(boost::bind(evtHandler, obj, _1));
//}


void CollisionSystem::receive(Message* message)
{
	if (*message == Message::CHUNK_UPDATE)
	{
		updateChunks();
	}
}

void CollisionSystem::onNotify(int entity, EventID event)
{
	//switch (event)
	//{
	//case EventID::CHUNK_UPDATE:
	//	updateChunks();
	//}
}

EventID CollisionSystem::checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const
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
		return EventID::COLLISION_BOTTOM;
	}
	// Collision over main object
	else if (b_collision < t_collision && b_collision < l_collision /*+ 1*/ && b_collision < r_collision /*- 1*/)
	{
		return EventID::COLLISION_TOP;
	}
	//	Collision to the right of main object
	else if (l_collision < r_collision && l_collision < t_collision /*+ 1*/ && l_collision < b_collision /*- 1*/)
	{
		return EventID::COLLISION_RIGHT;
	}
	//	Collision to the left of main object
	else if (r_collision < l_collision && r_collision < t_collision /*+ 1*/ && r_collision < b_collision /*- 1*/)
	{
		return EventID::COLLISION_LEFT;
	}
	//	If nothing collided after all (Probably because of corner of otherEntity)
	else
	{
		return EventID::COLLISION_FAULT;
	}
}

sf::Vector2f CollisionSystem::fixPositionOnCollide(EventID collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect)
{
	sf::Vector2f fixedPos(0, 0);

	switch (collDirection)
	{
	case EventID::COLLISION_BOTTOM:
	{
		//std::cout << "bottom\n";
		return sf::Vector2f(rect.left, otherRect.top - rect.height);
	}
	case EventID::COLLISION_RIGHT:
	{
		//std::cout << "right\n";
		return sf::Vector2f(otherRect.left - rect.width, rect.top);
	}
	case EventID::COLLISION_LEFT:
	{
		//std::cout << otherRect.left + otherRect.width << ", " << rect.top << '\n';
		return sf::Vector2f(otherRect.left + otherRect.width, rect.top);
	}
	case EventID::COLLISION_TOP:
		return sf::Vector2f(rect.left, otherRect.top + otherRect.height);
	case EventID::COLLISION_FAULT:
		return sf::Vector2f(rect.left, rect.top);
	}

	return fixedPos;
}
