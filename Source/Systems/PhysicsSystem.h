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
public:
								PhysicsSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

			//	Get notified from subscriptions
	void						receiveC(Collision* collision);
	void						receiveA(Action* action);
	//void						receiveT(MoveToPos* moveToPos);		//	Maybe move into own System?

private:
	void						addForce(Physics* physics, const sf::Vector2f nForce);
	void						doElasticCollision(Entity* a, Entity* b);

private:
	EntityManager entMan;
};