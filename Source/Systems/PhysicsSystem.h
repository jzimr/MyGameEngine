#pragma once
#include "stdafx.h"
#include "System.h"
#include <cmath>

////////////////////////////////////////////////////////////
/// Components used: Transform, Physics, Collider, Movement
///	 
////////////////////////////////////////////////////////////

class PhysicsSystem : public System
{
private:
	struct EntComponents;
	enum Collision : int;

public:
								PhysicsSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* entity) override;

	//	Get notified from subscriptions
	void				onNotify(int entity, Event event) override;

	////////////////////////////////////////////////////////////
	/// Methods for physics stuff
	///	
	////////////////////////////////////////////////////////////
private:
	//	Check collision on an entity
	Collision			checkCollision(const sf::Rect<float>& collider, const sf::Rect<float>& otherCollider, const sf::Vector2f velocity) const;

	enum Collision
	{
		COLLISION_RIGHT,
		COLLISION_LEFT,
		COLLISION_BOTTOM,
		COLLISION_TOP,
		COLLISION_FAULT
	};

private:
	struct EntComponents
	{
		Transform* transformComp;		//	Required
		Physics* physicsComp;			//	This or/and
		Collider* colliderComp;			//	this 
		Movement* movementComp;			//	physicsComp required

		EntComponents(Transform* trans, Physics* phys,
			Collider* coll, Movement* move)
			: transformComp{ trans }, physicsComp{ phys }, colliderComp{coll},
			movementComp{ move }
		{ 
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;
};