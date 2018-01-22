#include "player.h"
#include <iostream>
namespace games
{
    Player::Player(std::string name)
        : Renderable(200,200,30,30,"Sprite"), name(name)
    {
    }

    void Player::moveRight(const double & deltaTime)
    {
        rect.x += 0.5 * deltaTime;
    }

    void Player::moveLeft(const double & deltaTime)
    {
        rect.x -= 0.5 * deltaTime;
    }

    void Player::update(const std::vector< Renderable > & renderables, const int & gravity, const double & deltaTime)
    {
        if( !checkCollide( renderables ) )
        {
            rect.y += gravity * 0.1 * deltaTime;
        }
    }

    bool Player::checkCollide(const std::vector< Renderable > & renderables)
    {
        bool colliding = false;
        for(std::vector< Renderable >::size_type i = 0; i < renderables.size(); ++i)
        {
            if( renderables[i].isOverlapping( rect ) )
            {
                colliding = true;
            }
        }
        return colliding;
    }

    void Player::jump(const double &)
    {
    }
}
