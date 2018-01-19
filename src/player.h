#ifndef _PLAYER_
#define _PLAYER_
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace games
{
    class Player : public utils::Renderable
    {
        public:
            Player(std::string name);
    };
}
#endif
