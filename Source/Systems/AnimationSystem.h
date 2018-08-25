#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class AnimationSystem : public System
{
public:
								AnimationSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;

	//	Get notified from subscriptions
	void						receiver(Action* action);

private:
	void						flipTexture(sf::Texture& texture);

private:
	EntityManager				entMan;

};
