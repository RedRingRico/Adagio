#include <Game.hpp>
#include <iostream>

namespace Adagio
{
	Game::Game( )
	{
	}

	Game::~Game( )
	{
	}

	int Game::Initialise( )
	{
		if( this->PlatformInitialisation( ) != 0 )
		{
			std::cout << "Failed to initialise platform-specific resources" <<
				std::endl;
			return 1;
		}

		return 0;
	}

	int Game::Execute( )
	{
		return 0;
	}
}

