#pragma once
#include "stdafx.h"
#include <cassert>
#include "Constants.h"
#include <memory>
#include "Chunk.h"
#include "AnimatedSprite.hpp"
class Entity;

using namespace Settings;

enum COMP_TYPE
{
	//BASE_COMP = 0,
	//TRANSFORM_COMP = 0,
	PARENTABLE_COMP,
	PHYSICS_COMP,
	COLLIDER_COMP,
	PLAYER_COMP,
	LIVINGTHING_COMP,
	CONTROLLER_COMP,
	MOVEMENT_COMP,
	ANIM_COMP,
	SPRITE2D_COMP,
	GRABBABLE_COMP,
};

struct BaseComponent
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~BaseComponent() {};

//	VVVVVVVVVVVVVVVVVVVV	TODO: IMPLEMENT
	bool enabled = true;			// Is the component active?	
};

//	a = F/m

struct Physics : BaseComponent		//	Space Physics
{
	//float gravity = 0.0f;	//	Default gravity (Disabled in space)
	sf::Vector2f velocity = sf::Vector2f{ 0,0 };		//	DO NOT MANIPULATE THIS VALUE DIRECTLY!!!
	float maxSpeed = 30.0f;

	sf::Vector2f force = sf::Vector2f{ 0,0 };		//	If you want to add any temporary force to object
	float mass = 1.0f;

	COMP_TYPE type = PHYSICS_COMP;
};

struct Collider : BaseComponent		//	Collides with other objects
{
	sf::Rect<float> colliderBox;	//	Simply a box around the m_entity sprite
	//	 VVVVVVVVV -> TODO
	//bool isTrigger = false;			//	If true, this collider works as a trigger instead (E.g. death)

	COMP_TYPE type = COLLIDER_COMP;
};

struct Player : BaseComponent		//	Can only be applied to one m_entity at a time
{
	//	Maybe move VVVV into custom component?
	std::vector<std::unique_ptr<Chunk>> loadedChunks;		//	List with chunks that are currently active
	sf::View camera;

	bool inBuildingState = false;

	COMP_TYPE type = PLAYER_COMP;
};

struct LivingThing : BaseComponent		//	Change name, not descriptive enough
{
	Entity* holdingGrabbableObject = NULL/*, weapon = NULL*/;		

	COMP_TYPE type = LIVINGTHING_COMP;
};

///	Requires : MovementComponent
struct Controller : BaseComponent
{
	COMP_TYPE type = CONTROLLER_COMP;
};

///	Requires : PhysicsComponent
struct Movement : BaseComponent		//	Can be applied to NPC's as well
{
	//float horizontalSpeed = 30;
	////float runSpeed = 50;
	//float jumpForce = 200;
	//float velocityWithoutAdditionalForce = 20.0f;		//	Enabled when 
														//	1. A force that has exceeded this limit is no longer acting upon this object
														//	2. The object's velocity is not under this limit (Or standing still)
	float mSpeed = 500.0f;			//	normal movement speed

	COMP_TYPE type = MOVEMENT_COMP;
};

struct Anim : BaseComponent
{
	enum Layer
	{
		LAYER_BACK,
		LAYER_FRONT,
		LAYER_SIZE
	};
	enum AnimAction
	{
		MOVING = 0,		//	DON'T CHANGE ORDER!!!
		JUMPING = 1,
		STANDING = 2,
	};

	Layer layer;

	//short facingDirection = 1;					//	1 = Facing right, -1 = Facing left

	std::map<AnimAction, Animation> rightAnimations;			//	All possible animations with their triggers
	std::map<AnimAction, Animation> leftAnimations;				//	For both left and right
	std::map<AnimAction, sf::Texture> textures;
	AnimatedSprite activeAnim;

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

	//short facingDirection = 1;					//	1 = Facing right, -1 = Facing left

	Layer layer;
	sf::Texture texture;
	sf::Sprite sprite;

	COMP_TYPE type = SPRITE2D_COMP;
};

struct Grabbable : BaseComponent				//	If an object can be picked up
{
	COMP_TYPE type = GRABBABLE_COMP;
};