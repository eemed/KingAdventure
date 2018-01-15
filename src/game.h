#ifndef _GAME_
#define _GAME_
#include <string>
namespace utils
{
    class Game
    {
        public:
            virtual ~Game() {};
            virtual void runGame() = 0;
    };
}
#endif
