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
	bool						placeBuilding();

private:
	EntityManager entMan;
	std::shared_ptr<Entity> m_player;
	sf::RenderWindow& m_window;

	EntPtr buildingHeld;
};

//	Create buildingpart with parent-child relationship?

struct Building
{
	int buildingID;

	sf::Texture buildingTexture;
	sf::Sprite building;
};
