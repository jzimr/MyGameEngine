#pragma once

namespace Settings
{
	constexpr int WINDOW_X = 1280;
	constexpr int WINDOW_Y = 720;
	const int RESOLUTION_X = 640;
	const int RESOLUTION_Y = 360;
	constexpr float SPRITE_SCALE = 1.0f * WINDOW_X / RESOLUTION_X;
	const int WORLD_UNIT = 16 * SPRITE_SCALE;		//	1 world unit == 16 pixels
}