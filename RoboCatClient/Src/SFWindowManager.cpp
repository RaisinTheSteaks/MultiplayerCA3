#include <RoboCatClientPCH.h>

std::unique_ptr<sf::RenderWindow> SFWindowManager::sInstance;

bool SFWindowManager::StaticInit()
{
	sInstance.reset(new sf::RenderWindow(sf::VideoMode(1280, 720), "Shadow!"));
	return true;
}