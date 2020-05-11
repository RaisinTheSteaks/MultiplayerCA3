// Written by: Ronan

#ifndef LINE_HPP
#define LINE_HPP

class Line
{
public:
	Line();
	Line(sf::Vector2f pStart, sf::Vector2f pEnd, sf::Vector2f pNormal);

	bool InRect(sf::FloatRect p_rect);

	sf::Vector2f start;
	sf::Vector2f end;
	sf::Vector2f normal;
};
#endif