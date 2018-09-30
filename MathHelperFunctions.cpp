#include "stdafx.h"
#include "MathHelperFunctions.h"

namespace HelperFuncs
{
	float getLength(const sf::Vector2f& v)
	{
		return sqrtf(pow(v.x, 2) + pow(v.y, 2));
	}

	sf::Vector2f normalize(const sf::Vector2f& v)
	{
		float vLength = getLength(v);

		return sf::Vector2f(v.x / vLength, v.y / vLength);
	}

	float multiplyVectors(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	sf::Vector2f scaleVector(const float scalar, const sf::Vector2f& v)
	{
		return sf::Vector2f(scalar * v.x, scalar * v.y);
	}
}