#pragma once
#include "stdafx.h"
#include "Component.h"

class Test : public Component
{
public:
	Test(Entity* ent);
	int							getTest() const;



	//void				update(float dt);
	//void				draw(sf::RenderTarget& target, sf::RenderStates states);

private:
	int test;
};
