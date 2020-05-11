#include <RoboCatPCH.h>
#include <time.h>
#include <SDL.h>

std::unique_ptr< Engine >	Engine::sInstance;


Engine::Engine() :
mShouldKeepRunning( true )
{
	SocketUtil::StaticInit();

	srand( static_cast< uint32_t >( time( nullptr ) ) );
	
	GameObjectRegistry::StaticInit();


	World::StaticInit();

	ScoreBoardManager::StaticInit();

	// Didn't seem to have any effect turning it off by itself.
	//SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
}

Engine::~Engine()
{
	SocketUtil::CleanUp();

	SDL_Quit();
}




int Engine::Run()
{
	return DoRunLoop();
}

void Engine::HandleEvent( sf::Event &p_event )
{
	// Default implementation does nothing, up to derived classes to handle them, if they so choose
	( void )p_event;
}

bool Engine::PullEvent(sf::Event &p_event)
{
	return false;
}

int Engine::DoRunLoop()
{
	// Main message loop
	bool quit = false;

	sf::Event eve;

	while (!quit && mShouldKeepRunning)
	{
		while (PullEvent(eve))
		{
			if (eve.type == sf::Event::Closed)
			{
				quit = true;
			}
			else
			{
				HandleEvent(eve);
			}
		}

		Timing::sInstance.Update();

		DoFrame();
	}

	return eve.type;
}

void Engine::DoFrame()
{
	World::sInstance->Update();
}

	
