#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class RenderSystem : public System
{
public:
								RenderSystem();

	void						update(float dt, EventManager& events) override;

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	sf::FloatRect getViewBounds(const sf::View view);

private:
	sf::View* playerCamera;
	Entity* player;			//	Aquired in onEntityUpdate()

	EntityManager entMan;

};