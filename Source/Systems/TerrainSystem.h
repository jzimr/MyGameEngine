#pragma once
#include <random>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include "System.h"
#include "Chunk.h"
#include "TextureHolder.h"

using namespace Settings;
const int TABLE_SIZE = 256;

////////////////////////////////////////////////////////////
/// Components used: Transform, Player, 
///	The system manages chunks
////////////////////////////////////////////////////////////
class TerrainSystem : public System
{
public:
	typedef std::unique_ptr<Chunk> ChunkPtr;

public:
	TerrainSystem();			//	TODO: Add ability to add custom seed

	void						configure(EventManager& events) override;
	void						begin() override;
	void						update(float dt, EventManager& events) override;

private:
	void						updateChunks(EventManager& events);
	ChunkPtr					createChunk(int ID);
	void						loadTextures();

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
	std::vector<ChunkPtr> availableChunks;			//	Chunks that are not loaded				
	TextureHolder<std::string> textureHolder;

	int seed;
	float table[TABLE_SIZE];
	float d2_counter;



private:
	EntityManager entMan;

	Entity* player;
};
