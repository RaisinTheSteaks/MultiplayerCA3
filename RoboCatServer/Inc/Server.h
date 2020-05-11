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

	std::vector<Vector3> m_spawnPoints;

};