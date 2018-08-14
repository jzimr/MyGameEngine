#pragma once
#include "stdafx.h"
#include "System.h"

////////////////////////////////////////////////////////////
/// Components used: Transform, Collider
///	 
////////////////////////////////////////////////////////////
class CollisionSystem : public System
{

public:
	CollisionSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* entity) override;

	//	Get notified from subscriptions
	void				onNotify(int entity, Event event) override;

private:
	void						updateChunks();		//	Update collider on existing or new chunks
	//	Check collision on an entity
	Event						checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const;
	sf::Vector2f				fixPositionOnCollide(Event collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect);

private:
	struct EntComponents
	{
		Transform* transformComp;		//	Required
		Collider* colliderComp;			//	Required 
		Physics* physicsComp;			//	Not required (Entities who do not have this are static objects)

		EntComponents(Transform* trans, Collider* coll, Physics* phys)
			: transformComp{ trans }, colliderComp{ coll }, physicsComp{ phys }
		{
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;

	std::vector<Collider> terrainColliders;

	Player* playerComp;
};
