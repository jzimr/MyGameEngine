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

public:
								PhysicsSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* ent) override;

	//	Get notified from subscriptions
	void				onNotify(int entity, Event event) override;

	////////////////////////////////////////////////////////////
	/// Methods to perform physics stuff
	///	
	////////////////////////////////////////////////////////////
private:
	//	Add force to an entity
	void					addForce(Physics& physicsComp, sf::Vector2f velocity);
	//	Check collision on an entity
	bool					checkCollision(const EntComponents& entity, int ID) const;

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