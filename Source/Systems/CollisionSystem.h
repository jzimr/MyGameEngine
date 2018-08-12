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

private:
	//	Check collision on an entity
	Event						checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& otherRect) const;

private:
	struct EntComponents
	{
		Transform* transformComp;		//	Required
		Collider* colliderComp;			//	Required 

		EntComponents(Transform* trans, Collider* coll)
			: transformComp{ trans }, colliderComp{ coll }
		{
		}
	};


	std::map<int, std::unique_ptr<EntComponents>> entities;
};
