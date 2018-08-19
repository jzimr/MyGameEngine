#pragma once
#include <string>

enum class Event
{
	ENTITY_JUMP,			//	Trigger a jump event
	ENTITY_LEFT,			//	Go left
	ENTITY_RIGHT,			//	Go right
	STOP_ENTITY_LEFT,		//	Stop left movement
	STOP_ENTITY_RIGHT,		//	Stop right movement

	COLLISION_RIGHT,		//	Collision to the right of object
	COLLISION_LEFT,			//	Collision to the left   -- || --
	COLLISION_BOTTOM,		//	Collision on the bottom -- || --
	COLLISION_TOP,			//	Collision on the top	-- || --
	COLLISION_FAULT,		//	Collision was miscalculated

	CHUNK_UPDATE,			//	List with loaded chunks has been updated

	ENTITY_MOVING,			//	The entity is moving (velocity != 0)
	ENTITY_STOPPED_MOVING,	//	An entity has stopped moving (velocity == 0)
};
