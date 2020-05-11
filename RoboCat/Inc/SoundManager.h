class SoundManager
{
public:

	static void StaticInit();
	static std::unique_ptr< SoundManager >	sInstance;
	enum SoundToPlay
	{
		STP_Pickup = 1 << 0,
		STP_Shoot = 1 << 1,
		STP_Death = 1 << 2,
		STP_Join = 1 << 3
	};
	void PlaySound(SoundToPlay p_sound);
	void PlaySoundAtLocation(SoundToPlay p_sound, sf::Vector3f p_location);
	void PlayMusic();
protected:
	SoundManager();
	sf::Sound pickup, shoot, death, join;
	sf::SoundBuffer pickupB, shootB, deathB, joinB;
	sf::Music bgMusic;
	void LoadSoundFromFile(sf::Sound &p_sound, sf::SoundBuffer &p_buffer, string p_file);
	void LoadMusicFromFile(sf::Music &p_music, string p_file);
};