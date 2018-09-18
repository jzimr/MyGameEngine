#include "stdafx.h"
#include "BuildingSystem.h"

BuildingSystem::BuildingSystem(sf::RenderWindow& window)
	: m_window{ window }
{
}

void BuildingSystem::configure(EventManager& events)
{
	events.subscribe<Action>(this, &BuildingSystem::receive);
}

void BuildingSystem::update(float dt, EventManager& events)
{
	std::vector<std::shared_ptr<Entity>> list = entMan.getEntWithComp<Player>();		//	Spaghett
	m_player = list.empty() ? NULL : list[0];

	if (m_player && m_player->getComponent<Player>().inBuildingState)	//	If player wants to build
	{
		sf::Vector2f worldPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

		//	As of now, buildings are simply entities
		if (!buildingHeld)
			buildingHeld = entMan.createEntity("Wall", worldPos);

		buildingHeld->getComponent<Sprite2D>().sprite.setColor(sf::Color::Green);
		buildingHeld->setPosition(worldPos);
	}
	else
	{
		if (buildingHeld)
		{
			entMan.removeEntity(buildingHeld->getID());
			buildingHeld.reset();
		}
	}
}

bool BuildingSystem::placeBuilding()
{
	//	Add if statement to check if position is valid

	buildingHeld.reset();
	return true;
}

void BuildingSystem::receive(Action* action)
{
	if (action->m_action == action->ENTITY_BUILD)
	{
		Player* player = action->m_entity->hasComponent<Player>() ? &action->m_entity->getComponent<Player>() : NULL;

		if (player)
			player->inBuildingState = !player->inBuildingState;		//	Toggle playerstate
	}
	else if (action->m_action == action->ENTITY_CLICK_LEFT)
	{
		Player* player = action->m_entity->hasComponent<Player>() ? &action->m_entity->getComponent<Player>() : NULL;

		if (player && player->inBuildingState)
			if (placeBuilding())
				player->inBuildingState = false;
	}
}