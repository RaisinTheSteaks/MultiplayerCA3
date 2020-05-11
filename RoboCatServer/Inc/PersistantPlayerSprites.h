// Written by: Ronan

class PersistantPlayerSprites
{
public:
	static void StaticInit();
	static std::unique_ptr<PersistantPlayerSprites> sInstance;

	void Load();
	void AddPlayerEntry(std::string p_name, int p_id);
	int GetID(std::string p_name);

private:
	std::unordered_map<string, int> m_idMaps;
};