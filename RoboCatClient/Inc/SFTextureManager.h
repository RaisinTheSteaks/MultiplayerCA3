#pragma once

class SFTextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr<SFTextureManager> sInstance;

	SFTexturePtr GetTexture(const string& inTextureName);

private:
	SFTextureManager();

	bool CacheTexture(string inName, const char* inFileName);

	unordered_map< string, SFTexturePtr >	mNameToTextureMap;
};