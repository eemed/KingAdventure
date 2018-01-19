#ifndef _WORLD
#define _WORLD_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "utils.h"
namespace games
{
    // Represents the world current view
    class World
    {
        private:
            std::vector< utils::Renderable > renderables;
            std::vector< utils::Renderable > wholeWorld;
            int posX;
            int posY;
        public:
            //Load world from instruction file
            World(std::string filename);

            ~World();

            bool loadFromFile(std::string filename);
            // Determine what renderables to rendedr what to leave out
            std::vector< utils::Renderable > whatToRender();

            // Returns pointer to randerable or NULL if not overlapping
            utils::Renderable * isOverlapping() const;

            // Move world 
            void moveRight();
            void moveLeft();
            void moveUp();
            void moveDown();
    };
}
#endif
