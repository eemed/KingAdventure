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
      if( m_physics.get_velocity_y() < 0 )
      {
         m_hitbox.set_y( ceil(new_y) );
      }
      else // >= 0
      {
         m_hitbox.set_y( floor(new_y) );
      }
      set_jump_state();
      fix_collision();
      //std::cout << "Hbox: " << m_hitbox.get_x() << ", " << m_hitbox.get_y() << "\n";
   }

   void
   Player::set_jump_state()
   {
      if( hits_ground() )
      {
         m_jump_state = NOT_JUMPING;
      }
      else if( ceil(m_physics.get_velocity_y()) > 0 )
      {
         m_jump_state = FALL;
      }
      else if( m_physics.get_velocity_y() < 0 )
      {
         m_jump_state = RISE;
      }
      else if( m_jump_state == RISE and m_physics.get_velocity_y() == 0)
      {
         m_jump_state = TOP;
      }
   }

   void
   Player::hits_ground(bool n_hits) { m_on_ground = n_hits; }

   void
   Player::fix_collision()
   {
      //Replace this with something that searches nearby
      //collidables. Now uses worlds rendecontext.
      World * cur = World::current();
      bool is_hit = false;
      // -2 means prefer y collisions
      // 3 means prefer x collisions
      int padding = ( hits_ground() or (m_jump_state == FALL) ) ? -2 : 3;
      m_hitbox.set_y( m_hitbox.get_y() + 1);
      for( auto & elem : cur->get_render_context()->m_squares )
      {
         CollisionVector cv = rect_collides_with_rect( m_hitbox, elem, padding);
         if( cv.m_collision_info.m_bottom )
         {
            is_hit = true;
         }
         if( cv.m_collision_info.m_top )
         {
            m_physics.set_velocity_y(0.0f);
         }
         if( (cv.m_collision_info.m_right or cv.m_collision_info.m_left)/* and
               !hits_ground()*/ )
         {
            m_physics.set_velocity_x(0.0f);
         }
         m_hitbox.set_y( m_hitbox.get_y() + cv.m_y );
         m_hitbox.set_x( m_hitbox.get_x() + cv.m_x );
      }
      if( !is_hit )
      {
         m_physics.set_gravity_enabled(true);
         hits_ground(false);
      }
      else
      {
         m_physics.set_gravity_enabled(false);
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
   Player::speed_right(float elapsed_time)
   {
      m_physics.move_right(elapsed_time);
   }

   void
   Player::speed_left(float elapsed_time)
   {
      m_physics.move_left(elapsed_time);
   }

   void
   Player::jump()
   {
      if( hits_ground() )
      {
         m_physics.jump();
         m_jump_state = RISE;
      }
   }

   void
   Player::draw() const
   {
      m_hitbox.draw();
   }
}// sdl_platformer
