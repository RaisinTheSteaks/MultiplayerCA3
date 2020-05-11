// Written by: Ronan

#ifndef SHADOWFACTORY_HPP
#define SHADOWFACTORY_HPP

class ShadowFactory
{
public:
	static void StaticInit();
	static std::unique_ptr<ShadowFactory>	sInstance;

	std::vector<sf::VertexArray> getShadows(sf::Vector2f playerPosition, sf::Color color, sf::FloatRect p_bounds);
	bool load();
	bool doesCollideWithWorld(sf::FloatRect p_bounds);

private:
	std::vector<sf::FloatRect> shadowCasters;
	sf::Vector2f m_worldSize;

	std::vector<Line> getShadowLines();
	void optimizeShadowCasters();
	bool doesExitWithMapBounds(sf::FloatRect p_bounds);
	
};
#endif