#pragma once
#include "stdafx.h"
#include "System.h"
#include <queue>

////////////////////////////////////////////////////////////
/// Components used: Transform, Physics, Collider
///	 
////////////////////////////////////////////////////////////

class ControllerSystem : public System
{
private:
	struct EntComponents;

public:
	ControllerSystem();

	//void						init() override;
	void						update(float dt) override;
	void						onEntityUpdate(const Entity* entity) override;

	//	Get notified from subscriptions
	//	TODO: Maybe do some message handling with commands from event system in SFML?
	//void				onNotify(int entity, Event event) override;

	//	Called before everything else
	void						handleInput(std::queue<sf::Event>& events); 

private:
	struct EntComponents
	{
		Controller* controllerComp;

		EntComponents(Controller* contr)
			: controllerComp{ contr }
		{
		}
	};
	std::map<int, std::unique_ptr<EntComponents>> entities;
};