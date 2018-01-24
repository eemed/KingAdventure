#include "player.h"
#include <iostream>
#include <cstdlib>
#define MIN(a,b) ((a) < (b)) ? (a) : (b)
using namespace utils;
namespace games
{
    Player::Player(std::string name)
        : Renderable(46,200,30,30,"Sprite"), name(name),
        velocityX(0), velocityY(0), isJumping(false)
    {
    }

    void Player::speedRight(const double & deltaTime)
    {
        velocityX += 600 * deltaTime;
    }

    void Player::speedLeft(const double & deltaTime)
    {
        velocityX -= 600 * deltaTime;
    }

    void Player::moveRight(const double & deltaTime)
    {
        velocityX += 400 * deltaTime;
    }

    void Player::moveLeft(const double & deltaTime)
    {
        velocityX -= 400 * deltaTime;
    }
    void Player::update(std::vector< Renderable > & renderables, const double & deltaTime)
    {
        float friction = 0.5 * velocityX;
        float gravity = 30 * deltaTime;
        //printf("Gravity %f\n", gravity);
        velocityX -= friction;
        velocityY = MIN( velocityY + gravity, 9);
        if( abs( velocityX ) < 0.1 )
        {
            velocityX = 0;
        }
        rect.x += velocityX;
        rect.y += velocityY;
        for(std::vector< Renderable >::size_type i = 0; i < renderables.size(); ++i)
        {
            CollisionVector colV = checkCollision( renderables[i] );
            //If collision vectorY is < 0 correction force up
            if( colV.y < 0 and colV.x == 0)
            {
                velocityY = 0;
                isJumping = false;
            }
            //Hitting roof drop immediately
            if( colV.y > 0 )
            {
               velocityY = 0;
            }
            //Apply pos correction
            rect.x += colV.x;
            rect.y += colV.y;

        }
    }

    //float Player::checkHitGround(const std::vector< Renderable > & renderables)

    void Player::jump(const double & delta)
    {
        if( !isJumping )
        {
            if( delta == 1 )
                velocityY = 0;
            isJumping = true;
            velocityY = -10;
        }
    }

    //float Player::checkHitWall( SDL_Rect & r, const std::vector< Renderable > & renderables)

    CollisionVector Player::checkCollision( Renderable & r)
    {
        if( r.getYHigh() < getYLow() and r.getYLow() > getYHigh() )
        {
            if( r.getXHigh() > getXLow() and r.getXLow() < getXHigh() )
            {
                //Crossing
                int dirX = ( getMiddleX() - r.getMiddleX() );
                int dirY = ( getMiddleY() - r.getMiddleY() );

                int dx = getHalfXLen() + r.getHalfXLen() - ( abs(dirX) );
                int dy = getHalfYLen() + r.getHalfYLen() - ( abs(dirY) );
                if( abs(dx) < abs(dy) )
                {
                    if( dirX > 0 )
                    {
                        return CollisionVector(dx, 0);
                    }
                    else
                    {
                        return CollisionVector(-dx, 0);
                    }
                }
                else
                {
                    if( dirY > 0 )
                    {
                        return CollisionVector(0, dy);
                    }
                    else
                    {
                        return CollisionVector(0, -dy);
                    }
                }
            }
        }
        return CollisionVector(0,0);
    }
}
