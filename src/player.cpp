#include "player.h"
#include <iostream>
#include <cstdlib>
using namespace utils;
namespace games
{
    Player::Player(std::string name)
        : Renderable(370,400,30,30,"Sprite"), name(name),
        velocityX(0), velocityY(0), isJumping(false)
    {
    }

    void Player::moveRight(const double & deltaTime)
    {
        if( velocityX < 6 )
        {
            velocityX += 0.3 * deltaTime;
        }
    }

    void Player::moveLeft(const double & deltaTime)
    {
        if( velocityX > -6 )
        {
            velocityX -= 0.3 * deltaTime;
        }
    }

    void Player::update(std::vector< Renderable > & renderables, const double & deltaTime)
    {
        float friction = 0.5 * velocityX;
        float gravity = 0.25 * deltaTime;
        velocityX -= friction;
        std::cout << velocityX << ", " << velocityY << std::endl;
        if( velocityY > gravity )
        {
            velocityY = gravity;
        }
        else
        {
            velocityY += gravity;
        }
        if( abs( velocityX ) < 0.1 )
        {
            velocityX = 0;
        }
        rect.x += velocityX;
        rect.y += velocityY;
        if( velocityY >= 0 )
        {
            isJumping = false;
        }
        for(std::vector< Renderable >::size_type i = 0; i < renderables.size(); ++i)
        {
            CollisionVector colV = checkCollision( renderables[i] );
            rect.x += colV.x;
            rect.y += colV.y;
        }
    }

    //float Player::checkHitGround(const std::vector< Renderable > & renderables)

    void Player::jump(const double & delta)
    {
        if( !isJumping )
        {
            isJumping = true;
            velocityY -= 2.5 * delta;
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
