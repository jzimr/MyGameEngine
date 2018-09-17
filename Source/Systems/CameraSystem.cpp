#include "stdafx.h"
#include "CameraSystem.h"

using namespace Settings;

CameraSystem::CameraSystem(sf::RenderWindow& window)
	: m_window{ window }
{
}

void CameraSystem::update(float dt, EventManager& events)
{
	std::vector<EntPtr> p = entMan.getEntWithComp<Player>();		//	Temp
	player = p[0];
	playerCamera = &player->getComponent<Player>().camera;

	//	Setting up our camera
	playerCamera->setSize(RESOLUTION_X, RESOLUTION_Y);
	playerCamera->setCenter(player->getPosition());

	m_window.setView(*playerCamera);
}
