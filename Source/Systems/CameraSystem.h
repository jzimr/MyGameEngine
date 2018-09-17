#pragma once
#include "stdafx.h"
#include "System.h"
#include <map>
#include <memory>

class CameraSystem : public System
{
public:
	CameraSystem(sf::RenderWindow& window);

	void						update(float dt, EventManager& events) override;

private:
	sf::View* playerCamera;
	std::shared_ptr<Entity> player;			//	Aquired in onEntityUpdate()

	EntityManager entMan;
	sf::RenderWindow& m_window;
};