#pragma once
#include "stdafx.h"
#include <cassert>
#include "Constants.h"
#include <memory>
#include "Chunk.h"

using namespace Settings;

struct BaseComponent
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~BaseComponent() {};
};

struct Transform : BaseComponent	//	Position, rotation, scale
{
	sf::Transformable transform;
};

struct Physics : BaseComponent		//	Making an object fall
{
	float gravity = 400.0f;	//	Default gravity (Disable for e.g. bullets)
	sf::Vector2f velocity;
	float horizontalVelocity;

	const float maxFallingSpeed = 1000.0f;
};

struct Collider : BaseComponent		//	Collides with other objects
{
	sf::Rect<float> colliderBox;	//	Simply a box around the entity sprite
	//	 VVVVVVVVV -> TODO
	//bool isTrigger = false;			//	If true, this collider works as a trigger instead (E.g. death)
};

struct Player : BaseComponent		//	Can only be applied to one entity at a time
{
	//	Maybe move VVVV into custom component?
	std::vector<std::unique_ptr<Chunk>> loadedChunks;		//	List with chunks that are currently active
	//	Maybe add sf::View object here too so we can better load chunks?
};

///	Requires : MovementComponent
struct Controller : BaseComponent	
{
	
};

///	Requires : PhysicsComponent
struct Movement : BaseComponent		//	Can be applied to NPC's as well
{
	float horizontalSpeed = 200;
	//float runSpeed = 50;
	float jumpForce = 400;
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