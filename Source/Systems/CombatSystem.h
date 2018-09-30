#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class CombatSystem : public System
{
public:
	CombatSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

private:
	void						receive(Action* action);
	//void						

private:
	EntityManager entMan;

private:
};