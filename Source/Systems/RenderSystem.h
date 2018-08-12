#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class RenderSystem : public System
{
public:
								RenderSystem(/*sf::RenderWindow& window*/);

	//void						init() override;
	void						update(float dt) override;
	void						end() override;
	void						onEntityUpdate(const Entity* ent) override;

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	//sf::RenderWindow& mWindow;
	sf::View camera;
	const Entity* player;			//	Gotten in onEntityUpdate()

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