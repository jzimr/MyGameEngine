#pragma once
#include "stdafx.h"
#include "System.h"
#include "Constants.h"
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

	void						update(float dt, EventManager& events) override;

	//	Called before everything else
	void						handleInput(std::queue<sf::Event>& events); 

private:
	EntityManager entMan;
	std::queue<sf::Event>* m_eventQueue;
};