#include <RoboCatServerPCH.h>

std::unique_ptr<PersistantPlayerSprites> PersistantPlayerSprites::sInstance;

void PersistantPlayerSprites::StaticInit()
{
	PersistantPlayerSprites* pps = new PersistantPlayerSprites();
	pps->Load();
	sInstance.reset(pps);
}

void PersistantPlayerSprites::Load()
{
	// Load in the current file at the start to populate the map.
	std::ifstream inFile("../Assets/Saved/PersistantTexture.txt");
	std::string in;
	while (std::getline(inFile, in))
	{
		// Pase 'in'.
		auto delimPos = in.find_first_of(":");
		std::string name = in.substr(0, delimPos);
		std::string idStr = in.substr(delimPos + 1);
		int id = std::stoi(idStr);

		// Add to the map.
		m_idMaps.insert(std::pair<std::string, int>(name, id));
	}
}

void PersistantPlayerSprites::AddPlayerEntry(std::string p_name, int p_id)
{
	// See if it's already in the map.
	if (m_idMaps.find(p_name) != m_idMaps.end())
		return;

	// Only care about the remainder part.
	int modId = p_id % 9;

	// Add to the file.
	std::ofstream outFile("../Assets/Saved/PersistantTexture.txt", std::ofstream::out | std::ofstream::app);
	if (outFile.good())
	{
		outFile << p_name << ":" << modId << std::endl;
	}
	// Add to the map.
	m_idMaps.insert(std::pair<std::string, int>(p_name, modId));
}

int PersistantPlayerSprites::GetID(std::string p_name)
{
	// Return the value in the map.
	if (m_idMaps.find(p_name) != m_idMaps.end())
		return m_idMaps[p_name];
	else
		return -1;
}
