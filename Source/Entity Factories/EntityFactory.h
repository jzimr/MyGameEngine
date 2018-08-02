#pragma once
#include <memory>
class World;

class EntityFactory
{
public:
	EntityFactory(World* world);
	void						createPlayer();
	void						createGround();

private:
	World * mWorld;
};