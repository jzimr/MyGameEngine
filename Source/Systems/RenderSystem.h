#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class RenderSystem : public System
{
public:
								RenderSystem(/*sf::RenderWindow& window*/);

	void						init() override;
	void						update(float dt) override;
	void						end() override;

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	sf::FloatRect getViewBounds(const sf::View view);

private:
	sf::View camera;
	std::shared_ptr<Entity> player;			//	Aquired in onEntityUpdate()

	EntityManager entMan;

};