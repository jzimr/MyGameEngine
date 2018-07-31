#pragma once
#include "stdafx.h"
#include <cassert>

//enum Component
//{
//	COMPONENT_NONE,
//	COMPONENT_TRANSFORM,		//	ALWAYS REQUIRED
//	COMPONENT_SPRITE2D,
//	COMPONENT_SIZE
//};

struct BaseComponent						//	Can't use struct unfortunately, as
{										//	it does not support dynamic_casting
	virtual ~BaseComponent() {};
};

struct Transform : BaseComponent
{
	sf::Transformable transform;
};

struct Sprite2D : BaseComponent
{
	enum Layer
	{
		LAYER_BACK,
		LAYER_FRONT,
		LAYER_SIZE
	};

	Layer layer;
	sf::Texture texture;
	sf::Sprite sprite; 
};