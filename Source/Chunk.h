#pragma once
#include "stdafx.h"

struct Chunk		//	Maybe move back to TerrainSystem.h?
{
	int chunkID;	//	Unique ID of chunk 
							//int maxHeight = 30;		//	Max height of chunk (in blocks)
	float startPosX = 0;	//	Start on x axis
							//	float startPosY = 400;

	float amp = 40,				//	amplitude, also max height of chunk (in blocks)
		wl = 60,				//	wavelength
		fq = 1 / wl,			//	frequency
		offset = 0;				//	offset of the perlin noise function

	int octaves = 4;
	float persistence = 0.25f;		//	Lower = more smooth

	std::vector<sf::Sprite> topBlocks;
	std::vector<sf::Sprite> underBlocks;
	sf::Texture grassTex, dirtTex;		//	Put into a static array when more textures needed

	Chunk(int ID) : chunkID{ ID }
	{
		std::cout << "Chunk with id " << ID << " created\n";
	}
};
