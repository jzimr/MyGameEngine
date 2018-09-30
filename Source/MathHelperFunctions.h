#pragma once

namespace HelperFuncs
{
	float getLength(const sf::Vector2f& v);
	sf::Vector2f normalize(const sf::Vector2f& v);
	float multiplyVectors(const sf::Vector2f& a, const sf::Vector2f& b);
	sf::Vector2f scaleVector(const float scalar, const sf::Vector2f& v);
}