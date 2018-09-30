#include "stdafx.h"
#include "AnimationSystem.h"

typedef Action::EntAction EntAction;

AnimationSystem::AnimationSystem()
{
}

void AnimationSystem::configure(EventManager& events)
{
	events.subscribe<Action>(this, &AnimationSystem::receiver);
}

void AnimationSystem::update(float dt, EventManager& events)
{
	entities = entMan.getEntWithComp<Anim>();
	sf::Time time = sf::seconds(dt);			//	Convert deltatime to sf::Time

	for (auto& m_entity : entities)		//	Update all animations
	{
		m_entity->getComponent<Anim>().activeAnim.update(time);



	}
}

void AnimationSystem::receiver(Action* action)
{
	Anim* animComp = NULL;
	Sprite2D* spriteComp = NULL;

	if (action->m_entity->hasComponent<Anim>())
		animComp = &action->m_entity->getComponent<Anim>();
	else if (action->m_entity->hasComponent<Sprite2D>())
		spriteComp = &action->m_entity->getComponent<Sprite2D>();
	else
		return;

	switch (action->m_action)
	{
	case EntAction::ENTITY_RIGHT:
		if (animComp)
		{
			animComp->activeAnim.play(animComp->rightAnimations.find(Anim::MOVING)->second);
			animComp->activeAnim.setScale(1.0f, 1.0f);
		}
		else if (spriteComp)
		{
			sf::IntRect tRect = spriteComp->sprite.getTextureRect();

			spriteComp->sprite.setScale(1.0f, 1.0f);

			//if (tRect.width < 0)
			//	spriteComp->sprite.setTextureRect(sf::IntRect(0, 0, -1 * tRect.width, tRect.height));
		}
		break;
	case EntAction::ENTITY_LEFT:
		if (animComp)
		{
			animComp->activeAnim.play(animComp->leftAnimations.find(Anim::MOVING)->second);
			animComp->activeAnim.setScale(-1.0f, 1.0f);
		}
		else if (spriteComp)
		{
			sf::IntRect tRect = spriteComp->sprite.getTextureRect();

			spriteComp->sprite.setScale(-1.0f, 1.0f);

			//if(tRect.width > 0)
				//spriteComp->sprite.setTextureRect(sf::IntRect(/*tRect.width*/0, 0, -1 * tRect.width, tRect.height));
		}
		break;
	case EntAction::STOP_ENTITY_RIGHT:
		if (animComp)
		{
			animComp->activeAnim.play(animComp->rightAnimations.find(Anim::STANDING)->second);
			animComp->activeAnim.setScale(1.0f, 1.0f);
		}
		break;
	case EntAction::STOP_ENTITY_LEFT:
		if (animComp)
		{
			animComp->activeAnim.play(animComp->leftAnimations.find(Anim::STANDING)->second);
			animComp->activeAnim.setScale(-1.0f, 1.0f);
		}
		break;
	}

	//	Change the Sprite or Animation for its children as well using recursion
	if (action->m_entity->hasChildren())
	{
		for (auto& child : action->m_entity->getChildren())
		{
			action->m_entity = child;
			receiver(action);
		}
	}
}