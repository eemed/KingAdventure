#ifndef _WORLD
#define _WORLD_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "utils.h"
#include "player.h"
namespace games
{
    // Represents the world current view
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
            //Load world from instruction file
            //World(std::string filename);
            World(SDL_Renderer *, TTF_Font *, Player);

            ~World();

            //bool loadFromFile(std::string filename);
            // Determine what renderables to rendedr what to leave out
            //std::vector< utils::Renderable > whatToRender();
            void render();
            void runGame();

            // Returns pointer to randerable or NULL if not overlapping
            //utils::Renderable * isOverlapping(const SDL_Rect &) const;

            // Move world 
            //void moveRight();
            //void moveLeft();
            //void moveUp();
            //void moveDown();
    };
}
#endif
