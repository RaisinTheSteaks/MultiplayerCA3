#include <RoboCatClientPCH.h>

std::unique_ptr<TexturedWorld> TexturedWorld::sInstance;

void TexturedWorld::StaticInit()
{
	sInstance.reset(new TexturedWorld());
	sInstance->Load();
}

bool TexturedWorld::Load()
{
	if (!loadSprites())
		return false;
	return true;
}

std::vector<sf::Sprite>& TexturedWorld::getTexturedWorld()
{
	return m_spriteTiles;
}

bool TexturedWorld::loadSprites()
{
	sf::Sprite spr;
	int tileSize = 64;

	sf::Image texWorld;
	if (!texWorld.loadFromFile("../Assets/maps/map3.png"))
		return false;

	auto size = texWorld.getSize();
	std::string texID = "";

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			// Check for the colors.
			if (texWorld.getPixel(i, j) == sf::Color::White)
			{
				spr.setTexture(*SFTextureManager::sInstance->GetTexture("tile"));
				spr.setPosition(i * tileSize, j * tileSize);
				m_spriteTiles.push_back(spr);
			}
			else if (texWorld.getPixel(i, j) == sf::Color::Blue)
			{
				spr.setTexture(*SFTextureManager::sInstance->GetTexture("water"));
				spr.setPosition(i * tileSize, j * tileSize);
				m_spriteTiles.push_back(spr);
			}
			else if (texWorld.getPixel(i, j) == sf::Color::Black)
			{
				spr.setTexture(*SFTextureManager::sInstance->GetTexture("wood"));
				spr.setPosition(i * tileSize, j * tileSize);
				m_spriteTiles.push_back(spr);
			}
			else if (texWorld.getPixel(i, j) == sf::Color::Green)
			{
				spr.setTexture(*SFTextureManager::sInstance->GetTexture("grass"));
				spr.setPosition(i * tileSize, j * tileSize);
				m_spriteTiles.push_back(spr);
			}
			// Match against other colors.
			//else if () {}
		}
	}

	return true;
}
