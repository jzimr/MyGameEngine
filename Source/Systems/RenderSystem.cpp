#include "stdafx.h"
#include "RenderSystem.h"
#include "World.h"

using namespace Settings;

////////////////////////////////////////////////////////////
/// TODO: Divide the world into chunks, and load them whenever
///			the player is inside them instead.
////////////////////////////////////////////////////////////

RenderSystem::RenderSystem()
{
}

void RenderSystem::configure(EventManager& events)
{
}

void RenderSystem::update(float dt, EventManager& events)
{
	//	Create updates for some shit. E.g. That you do not need
	//	to draw all sprites unless inside the FOV of the client?

	entities.clear();
	///	Get all entities that have either Sprite2D or Anim Component
	std::vector<EntPtr> entSprites = entMan.getEntWithComp<Sprite2D>();
	std::vector<EntPtr> entAnims = entMan.getEntWithComp<Anim>();
	entities.reserve(entSprites.size() + entAnims.size());
	entities.insert(entities.end(), entSprites.begin(), entSprites.end());
	entities.insert(entities.end(), entAnims.begin(), entAnims.end());

	std::vector<EntPtr> p = entMan.getEntWithComp<Player>();
	player = p[0];

	camera.setCenter(player->getPosition());
}

void RenderSystem::end()		//	Fix the camera view, etc.
{
	camera.setSize(RESOLUTION_X, RESOLUTION_Y /*+ 200*/);
	//camera.zoom(4.0f);
}

void RenderSystem::draw(sf::RenderTarget & target/*, sf::RenderStates states*/)
{
	target.setView(camera);

	std::vector<EntPtr> p = entMan.getEntWithComp<Player>();		//	Temp
	player = p[0];

	Player* playerComp = &player->getComponent<Player>();
	sf::FloatRect viewBounds = getViewBounds(target.getView());

	//	Draw terrain sprites (As of now we simply loop through all chunks (Needs to be improved though!))
	for (const auto& lChunk : playerComp->loadedChunks)
	{
		sf::FloatRect sBounds;
		Chunk* chunk = lChunk.get();
		for (const auto& sprite : chunk->topBlocks)
		{
			sBounds = sprite.getGlobalBounds();
			if (sBounds.intersects(viewBounds))
				target.draw(sprite);
		}
		for (const auto& sprite : chunk->underBlocks)
		{
			sBounds = sprite.getGlobalBounds();
			if (sBounds.intersects(viewBounds))
				target.draw(sprite);
		}
	}	

	//	Draw m_entity sprites (This as well (look above))
	for (const auto& m_entity : entities)
	{
		//	If m_entity has both Sprite2D and Anim component, the Sprite2D will always be in favour
		bool isSprite2D = m_entity->hasComponent<Sprite2D>();

		sf::Drawable* drawableItem = isSprite2D ? (sf::Drawable*)&m_entity->getComponent<Sprite2D>().sprite :
			(sf::Drawable*)&m_entity->getComponent<Anim>().activeAnim;
		sf::Transformable* transItem = isSprite2D ? (sf::Transformable*) &m_entity->getComponent<Sprite2D>().sprite :
			(sf::Transformable*)&m_entity->getComponent<Anim>().activeAnim;

		transItem->setPosition(m_entity->getPosition()); 
		target.draw(*drawableItem);
	}
}

sf::FloatRect RenderSystem::getViewBounds(const sf::View view)
{
	sf::FloatRect rect;
	rect.left = view.getCenter().x - view.getSize().x / 2.0f;
	rect.top = view.getCenter().y - view.getSize().y / 2.0f;
	rect.width = view.getSize().x;
	rect.height = view.getSize().y;
	return rect;
}
