#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "TextureHolder.h"
#include <array>

class World : sf::NonCopyable
{
public:
								World(sf::RenderWindow& window);
	void						update(float dt);
	void						draw();

private:
	void						loadTextures();		//	Load all textures you want to use
	void						buildScene();

	enum Layer
	{
		Background,
		Front,
		LayerSize

	};

private:
	sf::RenderWindow&			mWindow;
	Entity						mSceneGraph;
	//	Each SceneNode here is an empty node that stores all children inside and updates them after the layer
	std::array<Entity*, Layer::LayerSize> mSceneLayers;	//	Array with all GameObjects divided into layers

	TextureHolder<std::string> textureHolder;		//	String can later be changed to an enum

	Entity* player;
};