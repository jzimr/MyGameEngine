#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class RenderSystem : public System
{
public:
								RenderSystem();

	void						configure(EventManager& events) override;
	void						update(float dt, EventManager& events) override;
	void						end() override;

	void						draw(sf::RenderTarget& target/*, sf::RenderStates states*/);

private:
	sf::FloatRect getViewBounds(const sf::View view);

private:
	sf::View camera;
	std::shared_ptr<Entity> player;			//	Aquired in onEntityUpdate()

	EntityManager entMan;

};