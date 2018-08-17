#pragma once
#include "stdafx.h"
#include "System.h"
//#include "Component.h"

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

	//	Get notified from subscriptions
	void				onNotify(int entity, Event event) override;

private:
	void						updateChunks();		//	Update collider on existing or new chunks
	//	Check collision on an entity
	Event						checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const;
	sf::Vector2f				fixPositionOnCollide(Event collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect);

private:
	EntityManager entMan;

	std::vector<Collider> terrainColliders;

	Player* playerComp;
};
