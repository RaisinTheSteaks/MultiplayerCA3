// Written by: Ronan

#ifndef TEXTUREDWORLD_HPP
#define TEXTUREDWORLD_HPP

class TexturedWorld
{
public:
	static void StaticInit();
	static std::unique_ptr<TexturedWorld> sInstance;

	bool Load();
	std::vector<sf::Sprite>& getTexturedWorld();

private:
	std::vector<sf::Sprite> m_spriteTiles;

	bool loadSprites();
};
#endif