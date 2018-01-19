#ifndef _PLATFORM_
#define _PLATFORM_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "utils.h"
namespace games
{
    class Platform : public utils::Renderable// Represents all objects you can collide with
    {
        public:
            Platform(int width, int height, std::string spritePath);
            ~Platform();
    };
}
#endif
