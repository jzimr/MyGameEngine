#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class AnimationSystem : public System
{
	//	Structure/TODO:
	//	- Holds all animations (Load them from folder) possible
	//	- Tag them by string name or enum? (Use map to bind them?)
	//	- 



public:
	AnimationSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* ent) override;

private:

	struct EntComponents
	{
		Anim* animComp;			//	Required

		EntComponents(Anim* anim)
			: animComp{ anim }
		{
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;

};
