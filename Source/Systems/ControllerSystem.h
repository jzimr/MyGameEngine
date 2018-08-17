#pragma once
#include "stdafx.h"
#include "System.h"
#include <queue>

////////////////////////////////////////////////////////////
/// Components used: Controller
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

	//	Get notified from subscriptions
	//	TODO: Maybe do some message handling with commands from event system in SFML?
	//void				onNotify(int entity, Event event) override;

	//	Called before everything else
	//	Maybe move the logic into update()?
	void						handleInput(std::queue<sf::Event>& events); 

private:

	EntityManager entMan;
};