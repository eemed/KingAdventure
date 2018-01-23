#ifndef _WORLD
#define _WORLD_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "utils.h"
#include "player.h"
namespace games
{
    // Represents the world
    class World
    {
        private:
            SDL_Renderer * renderer;
            TTF_Font * fnt;
            std::vector< utils::Renderable > renderables;
            std::vector< utils::Renderable > wholeWorld;
            int posX;
            int posY;
            Player player;
        public:
            World(SDL_Renderer *, TTF_Font *, Player);
            ~World();
            void render();
            void runGame();
            void update(const double & deltaTime);
    };
}
#endif
