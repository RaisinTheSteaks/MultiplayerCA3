#include <RoboCatClientPCH.h>

std::unique_ptr<FontManager> FontManager::sInstance;

void FontManager::StaticInit()
{
	sInstance.reset(new FontManager());
}

FontManager::FontManager()
{
	CacheFont("bebas", "../Assets/BebasNeue.OTF");
}

FontPtr FontManager::GetFont(const string & p_fontName)
{
	return mNameToFontMap[p_fontName];
}

bool FontManager::CacheFont(string inName, const char * inFileName)
{
	FontPtr newFont(new sf::Font());
	if (!newFont->loadFromFile(inFileName))
		return false;

	mNameToFontMap[inName] = newFont;
	return true;
}
