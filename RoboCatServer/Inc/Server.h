class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	RoboCatPtr	GetCatForPlayer( int inPlayerId );
	void	SpawnCatForPlayer( int inPlayerId );

	//Changes by Kevin
private:
	Server();
	float   TimeBetweenSpawns;
	float	SpawnTime;
	bool	InitNetworkManager();
	void	PickupUpdate();
	void	SetupWorld();

	struct SpawnPoint
	{
		SpawnPoint(Vector3 position, int playerId);

		Vector3 position;
		int playerId;
	};

	std::vector<SpawnPoint> m_spawnPoints;

};