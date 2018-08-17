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

void RenderSystem::init()
{
	//entities = entMan.getEntWithComps<Transform, Sprite2D>();
	//std::vector<EntPtr> p = entMan.getEntWithComp<Player>();
	//player = p[0];
}

void RenderSystem::update(float dt)
{
	//	Create updates for some shit. E.g. That you do not need
	//	to draw all sprites unless inside the FOV of the client?
	entities = entMan.getEntWithComps<Transform, Sprite2D>();
	std::vector<EntPtr> p = entMan.getEntWithComp<Player>();
	player = p[0];

	camera.setCenter(player->getComponent<Transform>().transform.getPosition());
}

void RenderSystem::end()		//	Fix the camera view, etc.
{
	camera.setSize(WINDOW_X, WINDOW_Y /*+ 200*/);
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

	//	Draw entity sprites (This as well (look above))
	for (const auto& entity : entities)
	{
		Sprite2D* reqComp = &entity->getComponent<Sprite2D>();
		Transform* transComp = &entity->getComponent<Transform>();

		reqComp->sprite.setPosition(transComp->transform.getPosition());
		//std::cout << transComp->transform.getPosition().x << '\n';
		target.draw(entity->getComponent<Sprite2D>().sprite);
	}

	//std::cout << target.getView().getSize().y << " ";
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
