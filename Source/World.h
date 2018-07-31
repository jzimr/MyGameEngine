#pragma once
#include "stdafx.h"
#include "Component.h"
#include "TextureHolder.h"
#include <array>
#include <bitset>
#include "Entity.h"
class SystemManager;

//struct Entity
//{
//	int ID;
//	std::bitset<COMPONENT_SIZE> components;
//};

class World : sf::NonCopyable
{
public:
	typedef std::unique_ptr<BaseComponent> CompPtr;

public:
								World(sf::RenderWindow& window);
	void						update(float dt);
	void						draw();

	//	This is only a test function
	void						createEntity();
	//	CREATE FUNCTION: void changeEntity(id, bitset<>);

private:
	void						loadTextures();		//	Load all textures you want to use
	void						buildScene();
	
	std::vector<std::unique_ptr<Entity>> entities;		//	List of all entities

private:
	sf::RenderWindow&			mWindow;
	//	Entity						mSceneGraph;
	//	Each Entity here is an empty node that stores all children inside and draws them after the layer
	//std::array<Entity*, Layer::LayerSize> mSceneLayers;	//	Array with all GameObjects divided into layers

	TextureHolder<std::string> textureHolder;		//	String can later be changed to an enum


	////////////////////////////////////////////////////////////
	/// Component System
	///	TODO: Implement own system that handles this
	////////////////////////////////////////////////////////////
	int uniqueEntID;
	SystemManager* systemManager;		//	Handles all system notifications etc.
};

////////////////////////////////////////////////////////////
/// Hierarchy structure of the scene
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
