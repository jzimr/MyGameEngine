#pragma once
#include "stdafx.h"
#include "TerrainSystem.h"
#include "System.h"
#include <vector>
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "ControllerSystem.h"
#include "CollisionSystem.h"
#include "AnimationSystem.h"
#include "CombatSystem.h"
#include <memory>
class EventManager;

enum class SystemEvent
{
	ENTITY_UPDATE,
};

//	Responsible to automatically add entities to the systems
class SystemManager
{
public:
	typedef std::unique_ptr<System> SysPtr;

public:
								SystemManager();

	void						configure();
	void						begin();
	void						update(float dt);
	void						end();

	void						notify(Entity* entity, SystemEvent event);

public:
	template<class T> T*	addSystem()
	{
		SysPtr newSys(new T());
		m_systems.push_back(std::move(newSys));
		return dynamic_cast<T*>(m_systems.back().get());
	}

	template<class T> T& getSystem() const
	{
		T* it = NULL;

		for (auto& system : m_systems)
		{
			it = dynamic_cast<T*>(system.get());
			if (it != NULL)
				break;
		}
		assert(it != NULL);

		return *it;
	}

private:
	std::vector<std::unique_ptr<System>> m_systems;
	EventManager m_eventManager;

};
