#include <RoboCatPCH.h>

Line::Line()
{
	start = sf::Vector2f();
	end = sf::Vector2f();
}

Line::Line(sf::Vector2f pStart, sf::Vector2f pEnd, sf::Vector2f pNormal)
{
	start = pStart;
	end = pEnd;
	normal = pNormal;
}

bool Line::InRect(sf::FloatRect p_rect)
{
	if (p_rect.contains(start) || p_rect.contains(end))
		return true;
	return false;
}
