#pragma once
#include "stdafx.h"
#include <cassert>
#include "Constants.h"
#include <memory>
#include "Chunk.h"
#include "AnimatedSprite.hpp"

using namespace Settings;

enum COMP_TYPE
{
	//BASE_COMP = 0,
	TRANSFORM_COMP = 0,
	PHYSICS_COMP,
	COLLIDER_COMP,
	PLAYER_COMP,
	CONTROLLER_COMP,
	MOVEMENT_COMP,
	ANIM_COMP,
	SPRITE2D_COMP,
};

struct BaseComponent
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~BaseComponent() {};
};

struct Transform : BaseComponent	//	Position, rotation, scale
{
	sf::Transformable transform;

	COMP_TYPE type = TRANSFORM_COMP;
};

struct Physics : BaseComponent		//	Making an object fall
{
	float gravity = 400.0f;	//	Default gravity (Disable for e.g. bullets)
	sf::Vector2f velocity = sf::Vector2f{ 0,0 };
	float horizontalVelocity = 0.0f;

	const float maxFallingSpeed = 1000.0f;

	COMP_TYPE type = PHYSICS_COMP;
};

struct Collider : BaseComponent		//	Collides with other objects
{
	sf::Rect<float> colliderBox;	//	Simply a box around the entity sprite
	//	 VVVVVVVVV -> TODO
	//bool isTrigger = false;			//	If true, this collider works as a trigger instead (E.g. death)

	COMP_TYPE type = COLLIDER_COMP;
};

struct Player : BaseComponent		//	Can only be applied to one entity at a time
{
	//	Maybe move VVVV into custom component?
	std::vector<std::unique_ptr<Chunk>> loadedChunks;		//	List with chunks that are currently active
	//	Maybe add sf::View object here too so we can better load chunks?

	COMP_TYPE type = PLAYER_COMP;
};

///	Requires : MovementComponent
struct Controller : BaseComponent	
{
	
	COMP_TYPE type = CONTROLLER_COMP;
};

///	Requires : PhysicsComponent
struct Movement : BaseComponent		//	Can be applied to NPC's as well
{
	float horizontalSpeed = 200;
	//float runSpeed = 50;
	float jumpForce = 270;

	COMP_TYPE type = MOVEMENT_COMP;
};

struct Anim : BaseComponent					//	Must have either Anim or Sprite2D, not both!
{
	enum Layer
	{
		LAYER_BACK,
		LAYER_FRONT,
		LAYER_SIZE
	};

	Layer layer;

	AnimatedSprite spriteAnimation;	

	COMP_TYPE type = ANIM_COMP;
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

	COMP_TYPE type = SPRITE2D_COMP;
};