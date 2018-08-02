#pragma once
#include "stdafx.h"
#include "System.h"

////////////////////////////////////////////////////////////
/// Components used: Transform, Physics, Collider
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


	////////////////////////////////////////////////////////////
	/// Methods to perform physics stuff
	///	
	////////////////////////////////////////////////////////////
private:
	//	Check collision on an entity
	bool					checkCollision(const EntComponents& entity, int ID) const;

private:
	struct EntComponents
	{
		Transform* transformComp;		//	Required
		Physics* physicsComp;			//	This or/and
		Collider* colliderComp;			//	this required

		EntComponents(Transform* trans, Physics* phys,
			Collider* coll)
			: transformComp{ trans }, physicsComp{ phys }, colliderComp{coll}
		{ 
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;
};