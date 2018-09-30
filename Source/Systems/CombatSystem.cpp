#include "stdafx.h"
#include "CombatSystem.h"

CombatSystem::CombatSystem()
{

}

void CombatSystem::configure(EventManager& events)
{
	events.subscribe<Action>(this, &CombatSystem::receive);
}

void CombatSystem::update(float dt, EventManager& events)
{

}

void CombatSystem::receive(Action* action)
{
	if (*action == action->ENTITY_CLICK_LEFT)
	{

	}
}

