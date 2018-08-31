#pragma once

namespace Settings
{
	const int MAX_COMPS = 64;
	constexpr int WINDOW_X = 1280;
	constexpr int WINDOW_Y = 720;
	const int RESOLUTION_X = 640;
	const int RESOLUTION_Y = 360;
	//constexpr float SPRITE_SCALE = 1.0f * WINDOW_X / RESOLUTION_X;
	const int WORLD_UNIT = 16/* / float(WINDOW_X / RESOLUTION_X)*/;

	const int MAX_CHUNKS_LOADED = 3;		//	Chunks loaded at the same time
	//	Maybe move below into Chunk struct?
	const int CHUNK_WIDTH = 16;			//	Chunk width in blocks

	const int GrabbableDistance = 80;		//	Minimum distance to be able to grab an object

	//const int SPRITE_SHEET_COLUMNS = 3;		//	Rows for the sprite sheet
}


//////////////////////////////////////////////
//
//	TODO: Put these enums in own header file!!
//
//////////////////////////////////////////////

const enum EventID
{
	BASE_EVENT,
	EXPLOSION,
	MESSAGE,
	COLLISION,
	ACTION,
	//MOVETOPOS,
};