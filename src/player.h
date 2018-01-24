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
            float velocityX;
            float velocityY;
            bool isJumping;
        public:
            Player(std::string name);
            void moveRight(const double &);
            void moveLeft(const double &);
            void speedRight(const double &);
            void speedLeft(const double &);
            void jump(const double &);
            void update(std::vector< utils::Renderable > &, const double &);
            //float checkHitGround(const std::vector< utils::Renderable > &);
            float checkHitWall(SDL_Rect &, const std::vector< Renderable > & renderables);
            utils::CollisionVector checkCollision( Renderable & );
    };
}
#endif
