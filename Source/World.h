#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Entity Factories/EntityFactory.h"
#include "Constants.h"
#include "EntityManager.h"

class World : sf::NonCopyable
{
public:
	typedef std::unique_ptr<BaseComponent> CompPtr;

public:
								World();

private:
	void						buildScene();
	EntityManager entMan;
	Entity* player;
};

////////////////////////////////////////////////////////////
/// Hierarchy structure of the scene (TO BE IMPLEMENTED)
/// 
////////////////////////////////////////////////////////////
//	|mSceneGraph
//	|	|mSceneLayers
//	|	|	|<Layer> Background
//	|	|	|	|<Entity> DesertBackground
//	|	|	|<Layer> Front
//	|	|	|	|<Entity> Player
//	|	|	|	|	|<Entity> Equipment
//	|	|	|	|	|	|<Entity> Sword
//	|	|	|	|	|	|<Entity> Armor	
//========================================
