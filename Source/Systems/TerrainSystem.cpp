#include "stdafx.h"
#include "TerrainSystem.h"




//	 _____            _                               _                                              _                    _ 
//	(____ \          ( )_       _                    | |                                            | |          _   _   | |
//	 _   \ \ ___  ___|/| |_    | |_  ___  _   _  ____| | _     ____  _   _     ___ ____   ____  ____| | _   ____| |_| |_ | |
//	| |   | / _ \|  _ \|  _)   |  _)/ _ \| | | |/ ___) || \   |    \| | | |   /___)  _ \ / _  |/ _  | || \ / _  )  _)  _)|_|
//	| |__/ / |_| | | | | |__   | |_| |_| | |_| ( (___| | | |  | | | | |_| |  |___ | | | ( ( | ( ( | | | | ( (/ /| |_| |__ _ 
//	|_____/ \___/|_| |_|\___)   \___)___/ \____|\____)_| |_|  |_|_|_|\__  |  (___/| ||_/ \_||_|\_|| |_| |_|\____)\___)___)_|
//	                                                                (____/        |_|         (_____|                                                                             




TerrainSystem::TerrainSystem()
	: textureHolder{}
	, seed{ 1 }
{
}

void TerrainSystem::configure(EventManager& events)
{
	loadTextures();
	generateTable();
}

void TerrainSystem::begin()
{
	//	Load chunks here if they are not in list
	//	E.g. if player teleports or dies
}

//	Only check for chunk updates every 1 second
void TerrainSystem::update(float dt, EventManager& events)
{
	d2_counter += dt;

	if (d2_counter > 1.0f)
	{
		entities = entMan.getEntWithComps<Sprite2D>();
		std::vector<EntPtr> p = entMan.getEntWithComp<Player>();		//	Spaghett
		player = p[0];

		updateChunks(events);

		d2_counter = 0.0f;
	}

	//	Maybe rather than every x seconds, get player position and check when player </> particular pos?
}

//	Currently only 3 chunks are loaded at once
void TerrainSystem::updateChunks(EventManager& events)		//	A bit messy, needs to be cleaned up
{
	float playerPosX = player->getPosition().x;
	//	Get chunk ID position where player is currently
	int playerChunkPos = (int)playerPosX / (CHUNK_WIDTH * WORLD_UNIT) 
		- (playerPosX < 0 /*&& playerPosX != (int)playerPosX*/);	//	Fix rounding for negative numbers
	std::vector<int> chunksToBeCreated;
	bool chunkUpdate = false;
	Player* playerComp = &player->getComponent<Player>();

	//	Fill array so we know what chunks are not in our available & player list
	for (int i = MAX_CHUNKS_LOADED / 2 * -1; i < MAX_CHUNKS_LOADED - 1; i++)
		chunksToBeCreated.push_back(playerChunkPos + i);

	std::vector<ChunkPtr>::iterator it;

	it = availableChunks.begin();
	//	Move from this list to player
	while (it != availableChunks.end())
	{
		Chunk* chunk = it->get();

		//	If chunk is inside range
		if (chunk->chunkID >= playerChunkPos - 1 && playerChunkPos + 1 >= chunk->chunkID)
		{
			//	Remove chunkID from list
			chunksToBeCreated.erase(std::remove(chunksToBeCreated.begin(), chunksToBeCreated.end(),
				chunk->chunkID), chunksToBeCreated.end());

			//	Move chunk to loaded
			playerComp->loadedChunks.push_back(std::move(*it));	//	This might be error prone
			it = availableChunks.erase(it);		//	Remove this element from list
			chunkUpdate = true;
		}
		else
			++it;
	}

	it = playerComp->loadedChunks.begin();
	//	Move from player to this list
	while (it != playerComp->loadedChunks.end())
	{
		Chunk* chunk = it->get();

		//	For our toBeCreated list
		if (chunk->chunkID >= playerChunkPos - 1 && playerChunkPos + 1 >= chunk->chunkID)
			chunksToBeCreated.erase(std::remove(chunksToBeCreated.begin(), chunksToBeCreated.end(),
				chunk->chunkID), chunksToBeCreated.end());

		//	If chunk is outside range
		if (chunk->chunkID < playerChunkPos - 1 || playerChunkPos + 1 < chunk->chunkID)
		{
			//	Move chunk to available
			availableChunks.push_back(std::move(*it));
			it = playerComp->loadedChunks.erase(it);
			chunkUpdate = true;
			continue;
		}
		++it;
	}

	//	Create new chunks if necessary (Place them into player list)
	for (int& ID : chunksToBeCreated)
	{
		playerComp->loadedChunks.push_back(createChunk(ID));
		chunkUpdate = true;
	}

	if (chunkUpdate)
	{
		Message chunkUp(Message::CHUNK_UPDATE);
		events.emit(chunkUp);		//	Entity ID does not matter here
	}

	///	Pseudocode for this function

	//	for each available chunk
		//	is chunk inside of player range?
			//	yes
				//	add chunk to player list	(remove from this list)
			//	no
				//	ignore

	//	for each loaded chunk
		//	is the player out of range of this chunk?
			//	yes
				//	unload the chunk
			//	no
				//	ignore(keep it loaded)
}

TerrainSystem::ChunkPtr TerrainSystem::createChunk(int ID)
{
	TerrainSystem::ChunkPtr chunk{ new Chunk(ID) };
	chunk->startPosX = ID * CHUNK_WIDTH * WORLD_UNIT;

	chunk->grassTex = textureHolder.get("Grass");
	chunk->dirtTex = textureHolder.get("Dirt");

	for (int i = chunk->startPosX / WORLD_UNIT; i < chunk->startPosX / WORLD_UNIT + CHUNK_WIDTH; i++)
	{
		///	Get the perlin noise values
		float x = i;
		float y = int(octaveNoise(x, chunk->octaves, chunk->persistence, chunk->fq,
			chunk->amp, chunk->offset) * chunk->amp);	//	Number between 0 and amp

														///	Create new sprite and resize it fitted to our resolution
		sf::Sprite newBlock;
		newBlock.setTexture(chunk->grassTex);
		newBlock.setPosition(x * WORLD_UNIT, y * WORLD_UNIT);
		chunk->topBlocks.push_back(newBlock);

		///	Create dirt underneath our grass block
		newBlock.setTexture(chunk->dirtTex);
		sf::Vector2f grassPos = newBlock.getPosition();

		//	Create blocks underneath it
		for (int i = 1; i <= 10; i++)
		{
			newBlock.setPosition(grassPos.x, grassPos.y + i * WORLD_UNIT);
			chunk->underBlocks.push_back(newBlock);
		}
	}
	return std::move(chunk);
}

void TerrainSystem::loadTextures()
{
	textureHolder.load("Grass", "Media/Textures/Grass.png");
	textureHolder.load("Dirt", "Media/Textures/Dirt.png");
}

float TerrainSystem::octaveNoise(float x, int octaves, float persistence, float frequency,
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

	return total / maxValue;
}

float TerrainSystem::noise(float x, bool makeSigned)
{
	int xi = (int)x - (x < 0 && x != (int)x);	//	Fix rounding for negative numbers
	int xMin = xi & (TABLE_SIZE - 1);
	float t = fade(x - xi);	//	0 if x is a natural number (negative numbers don't work afaik)
	int xMax = (xMin + 1) & (TABLE_SIZE - 1);

	return makeSigned ? 2 * lerp(table[xMin], table[xMax], t) - 1
		: lerp(table[xMin], table[xMax], t);
}

float TerrainSystem::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
//	Find the interpolation between two points (a & b) and parameter t
float TerrainSystem::lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

void TerrainSystem::generateTable()
{
	std::mt19937 mt_engine(seed);
	std::uniform_real_distribution<> gen_rnd(0.0, 1.0);

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		table[i] = gen_rnd(mt_engine);
	}
}