
#include <RoboCatClientPCH.h>

bool Client::StaticInit( )
{
	ConnectionDetails::StaticInit();

	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();

	InputManager::StaticInit();

	// New Versions.
	// Window manager needs to be initialized before RenderManager.
	// TextureManager before TexturedWorld
	SFWindowManager::StaticInit();
	SFTextureManager::StaticInit();
	SFRenderManager::StaticInit();
	FontManager::StaticInit();
	ShadowFactory::StaticInit();
	TexturedWorld::StaticInit();
	PlayerTextureGenerator::StaticInit();
	HUD::StaticInit();
	SoundManager::StaticInit();

	sInstance.reset( client );

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'RCAT', RoboCatClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnClient::StaticCreate );

	//string destination = StringUtils::GetCommandLineArg( 1 );
	string destination = ConnectionDetails::sInstance->GetClientDestination();
	//string name = StringUtils::GetCommandLineArg( 2 );
	string name = ConnectionDetails::sInstance->GetClientName();

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString( destination );

	NetworkManagerClient::StaticInit( *serverAddress, name );

	//NetworkManagerClient::sInstance->Set#PacketChance( 0.6f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.25f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.5f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.1f );
}



void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	SFRenderManager::sInstance->Render();

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent(sf::Event &p_event)
{
	sf::Vector2f in;
	switch (p_event.type)
	{
	case sf::Event::KeyPressed:
		InputManager::sInstance->HandleInput(EIA_Pressed, p_event.key.code);
		break;
	case sf::Event::KeyReleased:
		InputManager::sInstance->HandleInput(EIA_Released, p_event.key.code);
		break;
	case sf::Event::JoystickButtonPressed:
		if (p_event.joystickButton.button == 0) // A on Joystick
		{
			auto shootingKey = sf::Keyboard::K;
			InputManager::sInstance->HandleInput(EIA_Pressed, shootingKey);
		}
		break;
	case sf::Event::JoystickButtonReleased:
		if (p_event.joystickButton.button == 0) // A on Joystick
		{
			auto shootingKey = sf::Keyboard::K;
			InputManager::sInstance->HandleInput(EIA_Released, shootingKey);
		}
		break;
	default:
		break;
	}
}

bool Client::PullEvent(sf::Event &p_event)
{
	return SFWindowManager::sInstance->pollEvent(p_event);
}

