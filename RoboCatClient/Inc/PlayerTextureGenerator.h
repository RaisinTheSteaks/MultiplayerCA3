#pragma once

class PlayerTextureGenerator
{

public:

	static bool StaticInit();
	static std::unique_ptr<PlayerTextureGenerator>	sInstance;
	PlayerTextureGenerator();
	SFTexturePtr GetPlayerTexure(uint32_t p_id);

private:
	std::string ResolveID(uint32_t p_id);
	std::vector<std::string> m_playerTextureIDs;
};