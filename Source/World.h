#pragma once
#include "stdafx.h"
#include "Component.h"
#include "TextureHolder.h"
#include <array>
#include <bitset>
#include "Entity.h"
#include <memory>
#include <queue>
class SystemManager;

class World : sf::NonCopyable
{
public:
	typedef std::unique_ptr<BaseComponent> CompPtr;

public:
								World(sf::RenderWindow& window);
	void						update(float dt);
	void						draw();
	void						handleInput();

	void						addEntity(std::unique_ptr<Entity> entity);
	//Entity*					removeEntity();		//	REMEMBER TO NOTIFY SYSTEMS ABOUT ENTITY CHANGE

	int							getUniqueID();
	sf::Texture getTexture(std::string name) const;

	std::queue<sf::Event>& getEventQueue();

private:
	void						loadTextures();		//	Load all textures you want to use
	void						buildScene();
	
	std::vector<std::unique_ptr<Entity>> entities;		//	List of all entities

	std::queue<sf::Event> eventQueue;

private:

	TextureHolder<std::string> textureHolder;		//	String can later be changed to an enum
	sf::RenderWindow&			mWindow;
	//	Entity						mSceneGraph;
	//	Each Entity here is an empty node that stores all children inside and draws them after the layer
	//std::array<Entity*, Layer::LayerSize> mSceneLayers;	//	Array with all GameObjects divided into layers



	////////////////////////////////////////////////////////////
	/// Component System
	///	TODO: Implement own system that handles this
	////////////////////////////////////////////////////////////
	unsigned int uniqueEntID;			//	4,294,967,295 of unique ID's
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
