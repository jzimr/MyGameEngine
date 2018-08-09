#include "stdafx.h"
#include "Terrain.h"
#include "World.h"
#include "Constants.h"

using namespace Settings;

Terrain::Terrain(int s, const World* world)
	: seed(s)
	, mWorld(world)
{
	generateTable();
}
void Terrain::createChunk()
{
	Chunk* chunk = new Chunk();
	chunk->grassTex = mWorld->getTexture("Grass");
	chunk->dirtTex = mWorld->getTexture("Dirt");

	//int numSteps = 200;

	for (int i = 0; i < chunk->width; i++)
	{
		///	Get the perlin noise values
		float x = i;
		float y = int(octaveNoise(x, chunk->octaves, chunk->persistence, chunk->fq, 
			chunk->amp, chunk->offset) * chunk->amp);	//	Number between 0 and amp

		///	Create new sprite and resize it fitted to our resolution
		sf::Sprite newBlock;
		newBlock.setTexture(chunk->grassTex);
		newBlock.setScale(SPRITE_SCALE, SPRITE_SCALE);		//	Temporary
		newBlock.setPosition(x * WORLD_UNIT + chunk->startPosX, y * WORLD_UNIT);
		chunk->blocks.push_back(newBlock);

		///	Create dirt underneath our grass block
		newBlock.setTexture(chunk->dirtTex);
		sf::Vector2f grassPos = newBlock.getPosition();

			//	Create blocks underneath it
			for (int i = 1; i <= 10; i++)
			{
				newBlock.setPosition(grassPos.x, grassPos.y + i * WORLD_UNIT);
				chunk->blocks.push_back(newBlock);
			}
	}

	chunks.push_back(chunk);
}
float Terrain::octaveNoise(float x, int octaves, float persistence, float frequency,
	float amplitude, float offset, bool makeSigned)
{
	double total = 0;
	double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
	for (int i = 0; i < octaves; i++)
	{
		total += noise(x * frequency + offset) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;		//	maxvalue not used as we want the coordinates
}

float Terrain::noise(float x, bool makeSigned)
{
	int xi = (int)x - (x < 0 && x != (int)x);	//	Fix rounding for negative numbers
	int xMin = xi & (TABLE_SIZE - 1);
	float t = fade(x - xi);	//	0 if x is a natural number (negative numbers don't work afaik)
	int xMax = (xMin + 1) & (TABLE_SIZE - 1);

	return makeSigned ? 2 * lerp(table[xMin], table[xMax], t) - 1
		: lerp(table[xMin], table[xMax], t);
}

float Terrain::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
//	Find the interpolation between two points (a & b) and parameter t
float Terrain::lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

void Terrain::draw(sf::RenderTarget & target)
{
	for (auto& chunk : chunks)
	{
		for (auto& sprite : chunk->blocks)
		{
			target.draw(sprite);
		}
	}
}

void Terrain::generateTable()
{
	std::mt19937 mt_engine(seed);
	std::uniform_real_distribution<> gen_rnd(0.0, 1.0);

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		table[i] = gen_rnd(mt_engine);
	}
}