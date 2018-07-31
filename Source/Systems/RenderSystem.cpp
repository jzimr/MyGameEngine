#include "stdafx.h"
#include "RenderSystem.h"
#include "World.h"

RenderSystem::RenderSystem()
{
}

void RenderSystem::update(float dt)
{
	//	Create updates for some shit. E.g. That you do not need
	//	to draw all sprites unless inside the FOV of the client?
}

void RenderSystem::onEntityUpdate(Entity* entity)
{
	bool hasRequirements = entity->hasComponent<Sprite2D>()
		&& entity->hasComponent<Transform>();		//	0 or 1
	auto foundInMap = entities.find(entity->getID());

	//	False in Entity			
	if (!hasRequirements)
	{
		//	Not found in our list	=	No action
		if (foundInMap == entities.end())
			return;

		//	Found in our list		=	Remove from list
		else if (foundInMap != entities.end())
			entities.erase(entity->getID());
	}
	//	True in Entity
	else if (hasRequirements)
	{
		Sprite2D* playerSprite = &entity->getComponent<Sprite2D>();
		Transform* playerTrans = &entity->getComponent<Transform>();
		std::unique_ptr<RequiredComps> newInsert{ new RequiredComps(playerSprite, playerTrans) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

		//	Found in our list		=	Calibrate component adress
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}

void RenderSystem::draw(sf::RenderTarget & target/*, sf::RenderStates states*/)
{
	//	Draw all sprites
	for (auto& entity : entities)
	{
		sf::RenderStates state;
		state.transform = entity.second.get()->transformComp->transform.getTransform();
		target.draw(entity.second->spriteComp->sprite, state);
	}
}
