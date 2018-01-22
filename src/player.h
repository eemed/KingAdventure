#ifndef _PLAYER_
#define _PLAYER_
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace games
{
    class Player : public utils::Renderable
    {
        private:
            std::string name;
        public:
            Player(std::string name);
            void moveRight(const double &);
            void moveLeft(const double &);
            void jump(const double &);
            void update(const std::vector< utils::Renderable > &, const int &, const double &);
            bool checkCollide(const std::vector< utils::Renderable > &);
    };
}
#endif
