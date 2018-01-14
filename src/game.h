#ifndef _GAME_
#define _GAME_
namespace utils
{
    class Game
    {
        virtual void runGame( SDL_Renderer * ) = 0;
        virtual ~Game() {};
    };
}
#endif
