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

	//	Get notified from subscriptions
	void				onNotify(int entity, Event event) override;

	////////////////////////////////////////////////////////////
	/// Methods for physics stuff
	///	
	////////////////////////////////////////////////////////////
private:

	enum Collision
	{
		COLLISION_RIGHT,
		COLLISION_LEFT,
		COLLISION_BOTTOM,
		COLLISION_TOP,
		COLLISION_FAULT
	};

private:

	EntityManager entMan;
};