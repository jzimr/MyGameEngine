#pragma once
#include "stdafx.h"
#include "System.h"

class EntityInteractionSystem : public System
{
public:
	EntityInteractionSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

	//	Get notified from subscriptions
	void						receiver(Action* action);

private:
	void						handleGrabbing(Action* action);

private:
	EntityManager				entMan;

};
