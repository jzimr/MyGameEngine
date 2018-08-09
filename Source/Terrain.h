#pragma once
#include <random>
#include <vector>
#include "World.h"

const int TABLE_SIZE = 256;
//	Using perlin noise to generate 1D terrain
class Terrain
{
public:

public:
	Terrain(int s, const World* world);		//	s: seed

	//	For testing purposes
	void						draw(sf::RenderTarget& target);
	void						createChunk(/* ADD PARAMETERS FOR CUSTOM CHUNKS*/);		//	Chunk = 100 blocks



private:
	struct Chunk		//	When implementing into ECS, maybe make it a Component?
						//	^^	Makes it easier to implement into Renderer & physics system
	{
		const static int width = 200;	//	Width of chunk (in blocks)
		//int maxHeight = 30;		//	Max height of chunk (in blocks)
		float startPosX = 10;	//	Start on x axis
		//float startPosY = 400;

		float amp = 40,				//	amplitude, also max height of chunk (in blocks)
			wl = 60,				//	wavelength
			fq = 1 / wl,		//	frequency
			offset = 0;		//	offset of the perlin noise function

		int octaves = 4;
		float persistence = 0.25f;		//	Lower = more smooth

		std::vector<sf::Sprite> blocks;
		sf::Texture grassTex, dirtTex;		//	Put into a static array when it's growing
	};

	//sf::Sprite createBlock(Chunk* chunk, sf::Sprite sprite);

	////////////////////////////////////////////////////////////
	/// Methods for Perlin noise
	///	
	////////////////////////////////////////////////////////////

	float						octaveNoise(float x, int octaves, float persistence,
		float frequency, float amplitude, float offset, bool makeSigned = false);
	float						noise(float x, bool makeSigned = false);
	float						lerp(float a, float b, float t);
	float						fade(float t);

	void						generateTable();	//	Generate gradients (0.0  -  1.0) for this seed

private:
	std::vector<Chunk*> chunks;

	int seed;

	float table[TABLE_SIZE];

	const World* mWorld;			//	To get the textures 
};