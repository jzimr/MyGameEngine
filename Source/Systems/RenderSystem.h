#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class RenderSystem : public System
{
public:
								RenderSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(Entity* ent);

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	struct RequiredComps
	{
		Sprite2D* spriteComp;		//	NULL by default
		Transform* transformComp;

		RequiredComps(Sprite2D* sprite, Transform* trans)
			: spriteComp{ sprite }, transformComp{ trans }
		{
		}
	};
	std::map<int, std::unique_ptr<RequiredComps>> entities;
};