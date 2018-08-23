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

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

	//	Get notified from subscriptions
	void				onNotify(int entity, EventID event) override;

	void				receive(Message* message);		//	Add const and by reference

private:
	void						updateChunks();		//	Update collider on existing or new chunks
	//	Check collision on an entity
	EventID						checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const;
	sf::Vector2f				fixPositionOnCollide(EventID collDirection, const sf::Rect<float>& rect, const sf::Rect<float>& otherRect);

private:
	EntityManager entMan;

	std::vector<Collider> terrainColliders;

	Player* playerComp;
};
