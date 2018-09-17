#pragma once
#include "System.h"

class BuildingSystem : public System
{
public:
	BuildingSystem(sf::RenderWindow& window);

	void						configure(EventManager& events) override;

	void						update(float dt, EventManager& events) override;

	//	Get notified from subscriptions
	void						receive(Action* action);

private:
	void						spawnBuilding();

private:
	EntityManager entMan;
	std::shared_ptr<Entity> m_player;
	sf::RenderWindow& m_window;
};

//	Create buildingpart with parent-child relationship?

struct Building
{
	int buildingID;

	sf::Texture buildingTexture;
	sf::Sprite building;
};
