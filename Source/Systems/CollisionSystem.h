#pragma once
#include "stdafx.h"
//#include "Events.h"
#include "System.h"

typedef Collision::CollisionDirection CollisionDirection;

////////////////////////////////////////////////////////////
/// Components used: Transform, Collider
///	 
////////////////////////////////////////////////////////////
class CollisionSystem : public System
{

public:
	CollisionSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

	//	Get notified from subscriptions
	//void				onNotify(int entity, EventID event) override;

	void				receive(Message* message);		//	Add const and by reference

private:
	void						updateChunks();		//	Update collider on existing or new chunks
	//	Check collision on an entity
	CollisionDirection checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect);
	sf::Vector2f fixPositionOnCollide(CollisionDirection collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect);

private:
	EntityManager entMan;
	std::vector<Collider> terrainColliders;
	Player* playerComp;
};
