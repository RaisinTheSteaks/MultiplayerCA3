//Changes by Kevin
#include <RoboCatServerPCH.h>



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	ShadowFactory::StaticInit();
	ConnectionDetails::StaticInit();
	PersistantPlayerSprites::StaticInit();

	sInstance.reset( new Server() );
	return true;
}

Server::Server()
{

	GameObjectRegistry::sInstance->RegisterCreationFunction( 'RCAT', RoboCatServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnServer::StaticCreate );

	InitNetworkManager();

	TimeBetweenSpawns = 5.f;
	SpawnTime = 0.f;
	//NetworkManagerServer::sInstance->SetDropPacketChance( 0.8f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.25f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.5f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.1f );

	m_spawnPoints = {
		Vector3(128, 1088, 0),
		Vector3(64, 448, 0),
		Vector3(960, 1088, 0),
		Vector3(1216, 1088, 0),
		Vector3(768, 64, 0),
		Vector3(1728, 64, 0),
		Vector3(1728, 384, 0),
		Vector3(1728, 640, 0),
		Vector3(1728, 1088, 0),
		Vector3(1152, 1088, 0),
		Vector3(704, 832, 0)
	};

}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	uint16_t port = ConnectionDetails::sInstance->GetServerPort();
	return NetworkManagerServer::StaticInit( port );
}


namespace
{
	
	void CreateRandomMice( int inMouseCount )
	{
		Vector3 mouseMin( 0.f, 0.f, 0.f );
		Vector3 mouseMax(1920.f, 1280.f, 0.f );
		GameObjectPtr go;
		Vector3 mouseLocation;
		float size = 32;
		//make a mouse somewhere- where will these come from?
		for (int i = 0; i < inMouseCount; ++i)
		{
			go = GameObjectRegistry::sInstance->CreateGameObject('MOUS');
			do {
				mouseLocation = RoboMath::GetRandomVector(mouseMin, mouseMax);
			} while (ShadowFactory::sInstance->doesCollideWithWorld(sf::FloatRect(mouseLocation.mX - (size / 2), mouseLocation.mY - (size / 2), size, size)));
			go->SetLocation(mouseLocation);
		}
	}


}
void Server::PickupUpdate()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (Timing::sInstance.GetFrameStartTime() > SpawnTime)
	{
		SpawnTime = time + TimeBetweenSpawns;
		CreateRandomMice(1);
	}
}

void Server::SetupWorld()
{
	//spawn some random mice
	CreateRandomMice( 1 );
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnCats();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
	
	this->PickupUpdate();
}

void Server::HandleNewClient( ClientProxyPtr inClientProxy )
{
	
	int playerId = inClientProxy->GetPlayerId();
	
	ScoreBoardManager::sInstance->AddEntry( playerId, inClientProxy->GetName() );
	SpawnCatForPlayer( playerId );

}

void Server::SpawnCatForPlayer( int inPlayerId )
{
	RoboCatPtr cat = std::static_pointer_cast< RoboCat >( GameObjectRegistry::sInstance->CreateGameObject( 'RCAT' ) );
	cat->SetColor( ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
	cat->SetPlayerId( inPlayerId );
	
	// Pick one of a few random locations.
	int randomIndex = rand() % m_spawnPoints.size();
	cat->SetLocation( m_spawnPoints[randomIndex] );


}

void Server::HandleLostClient( ClientProxyPtr inClientProxy )
{
	//kill client's cat
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry( playerId );
	RoboCatPtr cat = GetCatForPlayer( playerId );
	if( cat )
	{
		cat->SetDoesWantToDie( true );
	}
}

RoboCatPtr Server::GetCatForPlayer( int inPlayerId )
{
	//run through the objects till we find the cat...
	//it would be nice if we kept a pointer to the cat on the clientproxy
	//but then we'd have to clean it up when the cat died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for( int i = 0, c = gameObjects.size(); i < c; ++i )
	{
		GameObjectPtr go = gameObjects[ i ];
		RoboCat* cat = go->GetAsCat();
		if( cat && cat->GetPlayerId() == inPlayerId )
		{
			return std::static_pointer_cast< RoboCat >( go );
		}
	}

	return nullptr;

}