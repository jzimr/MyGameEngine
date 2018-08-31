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
	//enum Collision : int;

public:
								PhysicsSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

			//	Get notified from subscriptions
	void						receiveC(Collision* collision);
	void						receiveA(Action* action);
	//void						receiveT(MoveToPos* moveToPos);		//	Maybe move into own System?

private:
	EntityManager entMan;
};