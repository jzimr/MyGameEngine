#include "stdafx.h"
#include "AnimationSystem.h"

AnimationSystem::AnimationSystem()
{

}

void AnimationSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComp<Anim>();
	sf::Time time = sf::seconds(dt);			//	Convert deltatime to sf::Time

	for (auto& entity : entities)		//	Update all animations
	{
		//entity->getComponent<Anim>().activeAnim.setAnimation(entity->getComponent<Anim>().animationMap.find(Anim::STANDING)->second);
		entity->getComponent<Anim>().activeAnim.update(time);



	}
}

void AnimationSystem::onNotify(int entity, EventID event)
{
	Anim* animComp = NULL;

	//	Find the entity
	for (const auto& ent : entities)
	{
		if (ent->getID() == entity)
		{
			animComp = &ent->getComponent<Anim>();
			break;
		}
	}

	switch (event)
	{
	case EventID::ENTITY_RIGHT:
		animComp->activeAnim.play(animComp->rightAnimations.find(Anim::MOVING)->second);
		animComp->activeAnim.setScale(1.0f, 1.0f);
		break;
	case EventID::STOP_ENTITY_RIGHT:
		animComp->activeAnim.play(animComp->rightAnimations.find(Anim::STANDING)->second);
		animComp->activeAnim.setScale(1.0f, 1.0f);
		break;
	case EventID::ENTITY_LEFT:
		animComp->activeAnim.play(animComp->leftAnimations.find(Anim::MOVING)->second);
		animComp->activeAnim.setScale(-1.0f, 1.0f);
		break;
	case EventID::STOP_ENTITY_LEFT:
		animComp->activeAnim.play(animComp->leftAnimations.find(Anim::STANDING)->second);
		animComp->activeAnim.setScale(-1.0f, 1.0f);
		break;
	}
}

void AnimationSystem::flipTexture(sf::Texture& texture)
{
	
}