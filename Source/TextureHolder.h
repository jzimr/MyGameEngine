#pragma once
#include "stdafx.h"
#include <map>
#include <cassert>
#include <utility>
#include <memory>

template<typename Identifier>
class TextureHolder
{
public:
						TextureHolder();

	void				load(const Identifier identifier, const std::string fileName);
	//	Another load with rect (Use "Parameter" typename)

	sf::Texture			get(const Identifier identifier) const;

private:
	void				insertResource(Identifier id, std::unique_ptr<sf::Texture> texture);

private:
	std::map<Identifier, std::unique_ptr<sf::Texture>> textureMap;
};

#include "TextureHolder.inl"