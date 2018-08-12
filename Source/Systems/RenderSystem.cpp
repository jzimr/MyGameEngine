#include "stdafx.h"
#include "RenderSystem.h"
#include "World.h"

using namespace Settings;

////////////////////////////////////////////////////////////
/// TODO: Divide the world into chunks, and load them whenever
///			the player is inside them instead.
////////////////////////////////////////////////////////////

RenderSystem::RenderSystem(/*sf::RenderWindow& window*/)
	//: mWindow{ window }
{
}

void RenderSystem::update(float dt)
{
	//	Create updates for some shit. E.g. That you do not need
	//	to draw all sprites unless inside the FOV of the client?

	camera.setCenter(player->getComponent<Transform>().transform.getPosition());
}

void RenderSystem::end()		//	Fix the camera view, etc.
{
	camera.setSize(WINDOW_X, WINDOW_Y + 200);
	camera.zoom(2.0f);
}

void RenderSystem::draw(sf::RenderTarget & target/*, sf::RenderStates states*/)
{
	target.setView(camera);

	//	Draw all sprites
	for (auto& entity : entities)
	{
		EntComponents* reqComp = entity.second.get();
		reqComp->spriteComp->sprite.setPosition(reqComp->transformComp->transform.getPosition());
		target.draw(entity.second->spriteComp->sprite);
	}

	//std::cout << target.getView().getSize().y << " ";
}

void RenderSystem::onEntityUpdate(const Entity* entity)
{
	int entityID = entity->getID();
	bool hasRequirements = entity->hasComponent<Sprite2D>()
		&& entity->hasComponent<Transform>();		//	0 or 1
	auto foundInMap = entities.find(entityID);
	
	//	Get the player (For camera)
	if (entity->hasComponent<Player>())
		player = entity;

	//	False in Entity			
	if (!hasRequirements)
	{
		//	Not found in our list	=	No action
		if (foundInMap == entities.end())
			return;

		//	Found in our list		=	Remove from list
		else if (foundInMap != entities.end())
			entities.erase(entityID);
	}
	//	True in Entity
	else if (hasRequirements)
	{
		Sprite2D* playerSprite = &entity->getComponent<Sprite2D>();
		Transform* playerTrans = &entity->getComponent<Transform>();
		std::unique_ptr<EntComponents> newInsert{ new EntComponents(playerSprite, playerTrans) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entityID, std::move(newInsert)));	//	Add to list

		//	Found in our list		=	Calibrate component adress
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}
