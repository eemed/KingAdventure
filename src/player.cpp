#include <iostream>
#include <cmath>

#include "player.h"
#include "collision.h"
#include "world.h"
#include "current.h"

namespace sdl_platformer
{
   Player::Player(int x, int y, int width, int height,
         Color col, std::string name)
      : m_hitbox(Rectangle(x, y, width, height, col)),
        m_physics( Physics()),
        m_name( name ),
        m_on_ground(true),
        m_jump_state( NOT_JUMPING )
   {
   }

   std::string
   Player::get_name() const { return m_name; }

   bool
   Player::hits_ground() const { return m_on_ground; }

   jump_state
   Player::get_jump_state() const { return m_jump_state; }

   void
   Player::update(float elapsed_time)
   {
      m_physics.update(elapsed_time);

      float new_x = m_hitbox.get_x() + m_physics.get_velocity_x();
      float new_y = m_hitbox.get_y() + m_physics.get_velocity_y();

      if( m_physics.get_velocity_x() < 0 )
      {
         m_hitbox.set_x( ceil(new_x) );
      }
      else // >= 0
      {
         m_hitbox.set_x( floor(new_x) );
      }
      m_hitbox.set_y( new_y );
      collides();
      //std::cout << "Hbox: " << m_hitbox.get_x() << ", " << m_hitbox.get_y() << "\n";
   }

   void
   Player::hits_ground(bool n_hits) { m_on_ground = n_hits; }

   void
   Player::collides()
   {
      //Replace this with something that searches nearby
      //collidables. Now uses worlds rendecontext.
      World * cur = World::current();
      bool is_hit = false;
      m_hitbox.set_y( m_hitbox.get_y() + 1);
      for( auto & elem : cur->get_render_context()->m_squares )
      {
         CollisionVector cv = rect_collides_with_rect( m_hitbox, elem );
         if( cv.m_hit )
         {
            is_hit = true;
         }
         m_hitbox.set_y( m_hitbox.get_y() + cv.m_y );
         m_hitbox.set_x( m_hitbox.get_x() + cv.m_x );
      }
      if( !is_hit )
      {
         hits_ground(false);
      }
      else
      {
         hits_ground(true);
         m_physics.set_velocity_y(0.0f);
      }
   }

   void
   Player::move_right(float elapsed_time)
   {
      m_physics.move_right(elapsed_time);
   }

   void
   Player::move_left(float elapsed_time)
   {
      m_physics.move_left(elapsed_time);
   }

   void
   Player::jump()
   {
      if( hits_ground() )
         m_physics.jump();
   }

   void
   Player::draw() const
   {
      m_hitbox.draw();
   }
}// sdl_platformer
