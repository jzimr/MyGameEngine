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
	void						onEntityUpdate(const Entity* ent) override;

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	struct EntComponents
	{
		Sprite2D* spriteComp;			//	Required
		Transform* transformComp;		//	Required

		EntComponents(Sprite2D* sprite, Transform* trans)
			: spriteComp{ sprite }, transformComp{ trans }
		{
			//std::cout << "rendersystem: " << transformComp->transform.getPosition().x << '\n';
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;
};