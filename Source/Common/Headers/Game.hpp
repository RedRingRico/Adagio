#ifndef __ADAGIO_GAME_HPP__
#define __ADAGIO_GAME_HPP__

namespace Adagio
{
	class Game
	{
	public:
		Game( );
		~Game( );

		int Initialise( );
		int Execute( );

	private:
		Game( const Game &p_Game );
		Game &operator=( const Game &p_Game );

		int PlatformInitialisation( );
	};
}

#endif // __ADAGIO_GAME_HPP__

