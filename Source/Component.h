#pragma once
#include "stdafx.h"
#include <cassert>

struct BaseComponent
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~BaseComponent() {};
};

struct Transform : BaseComponent
{
	sf::Transformable transform;
};

struct Physics : BaseComponent
{
	const float gravity = 9.81f;	//	All objects have the same gravity
	sf::Vector2f velocity;
};

struct Collider : BaseComponent
{
	sf::Rect<float> colliderBox;	//	Simply a box around the entity sprite
	bool isTrigger = false;			//	If true, this collider works as a trigger instead
};

struct Sprite2D : BaseComponent
{
	enum Layer
	{
		LAYER_BACK,
		LAYER_FRONT,
		LAYER_SIZE
	};

	//Sprite2D() {}
	//Sprite2D(sf::Texture tex, sf::Sprite spr, Layer lay = LAYER_FRONT)
	//	: texture{ tex }, sprite{ spr }, layer{ lay }
	//{
	//}

	Layer layer;
	sf::Texture texture;
	sf::Sprite sprite;
};