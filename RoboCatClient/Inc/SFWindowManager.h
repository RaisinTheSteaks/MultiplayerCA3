#pragma once

class SFWindowManager
{

public:

	static bool StaticInit();
	static std::unique_ptr< sf::RenderWindow >	sInstance;
};