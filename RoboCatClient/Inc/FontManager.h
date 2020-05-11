#pragma once

class FontManager
{
public:
	static void StaticInit();

	static std::unique_ptr<FontManager> sInstance;

	FontPtr GetFont(const string& p_fontName);

private:
	FontManager();

	bool CacheFont(string inName, const char* inFileName);

	unordered_map< string, FontPtr >	mNameToFontMap;
};