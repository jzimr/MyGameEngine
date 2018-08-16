#include "stdafx.h"
#include "AnimationSystem.h"





void AnimationSystem::onEntityUpdate(const Entity* entity)
{
	int entityID = entity->getID();
	bool hasRequirements = entity->hasComponent<Anim>();
	auto foundInMap = entities.find(entityID);

	//	False in entity
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
		Anim* entityAnim = &entity->getComponent<Anim>();

		std::unique_ptr<EntComponents> newInsert{ new EntComponents(entityAnim) };

		//	Not found in our list	=	Add to list
		if (foundInMap == entities.end())
			entities.insert(std::make_pair(entity->getID(), std::move(newInsert)));	//	Add to list

																					//	Found in our list		=	Calibrate component adress (just in case)
		else if (foundInMap != entities.end())
			foundInMap->second = std::move(newInsert);
	}
}