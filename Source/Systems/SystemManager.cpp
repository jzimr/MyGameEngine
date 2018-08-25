#include "stdafx.h"
#include "SystemManager.h"
#include "World.h"

SystemManager::SystemManager(/*sf::RenderWindow& window*/)
	: m_systems{}
	, m_eventManager{}
{
	configure();
}

void SystemManager::configure()
{
	//	Initialize all systems (THE ORDER MATTERS!)
	ControllerSystem* controller = addSystem<ControllerSystem>();	//	Must come first
	PhysicsSystem* physics = addSystem<PhysicsSystem>();
	CollisionSystem* collision = addSystem<CollisionSystem>();
	TerrainSystem* terrain = addSystem<TerrainSystem>();
	AnimationSystem* animation = addSystem<AnimationSystem>();		//	Right before rendering (Not required, but more clean (I guess?))
	RenderSystem* render = addSystem<RenderSystem>();				//	Must come last


	//	Add observers
	controller->addObserver(animation);			//	To change animation frame
	controller->addObserver(physics);			//	To change e.g. velocity
	collision->addObserver(physics);			//	To stop velocity if collision happened
	//terrain->addObserver(collision);			//	To add colliders to terrain


	for (auto& system : m_systems)		//	Update all systems
		system->configure(m_eventManager);
}

void SystemManager::begin()
{
	//	Do system stuff here...
	//	Check for new entities added
		//	If yes, add them to the systems

	for (auto& system : m_systems)
		system->begin();
}

void SystemManager::update(float dt)
{
	//	Do system stuff here...

	begin();				//	Might be wrong because of time etc.

	for (auto& system : m_systems)		//	For each system
		system->update(dt, m_eventManager);

	end();					//	Might also be wrong because of deltatime
}

void SystemManager::end()
{
	//	Do system stuff here...
	//	Get all system messages, and dispatch them in
	//	specific order. E.g. First controls, then physics
	//	, ...., and at end rendering

	for (auto& system : m_systems)
		system->end();
}

void SystemManager::notify(Entity * entity, SystemEvent event)
{
	for (auto& system : m_systems)
	{
		switch (event)
		{
		case SystemEvent::ENTITY_UPDATE:	break;		//	Not in use anymore
		}
	}
}