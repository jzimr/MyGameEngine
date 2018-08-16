#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class CombatSystem : public System
{
public:
	CombatSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* ent) override;


private:
	struct EntComponents
	{
		Sprite2D* spriteComp;			//	Required
		Transform* transformComp;		//	Required

		EntComponents(Sprite2D* sprite, Transform* trans)
			: spriteComp{ sprite }, transformComp{ trans }
		{
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;

};