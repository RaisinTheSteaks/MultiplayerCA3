#include <RoboCatClientPCH.h>

std::unique_ptr<PlayerTextureGenerator> PlayerTextureGenerator::sInstance;

PlayerTextureGenerator::PlayerTextureGenerator()
{
	m_playerTextureIDs = {
		/*"hitman", 
		"hatman",
		"man_blue",
		"man_brown",
		"man_old",
		"robot",
		"soldier",
		"woman",
		"zombie"*/
		"roman",
		"frigate"
	};
}

SFTexturePtr PlayerTextureGenerator::GetPlayerTexure(uint32_t p_id)
{
	
	return SFTextureManager::sInstance->GetTexture(ResolveID(p_id));
}

std::string PlayerTextureGenerator::ResolveID(uint32_t p_id)
{
	return m_playerTextureIDs[p_id % m_playerTextureIDs.size()];
}

bool PlayerTextureGenerator::StaticInit()
{
	sInstance.reset(new PlayerTextureGenerator());
	return true;
}
