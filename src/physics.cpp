#include <iostream>
#include <cstdlib>
#include <cmath>

#include "physics.h"
#include "world.h"
#include "collision.h"
#include "current.h"

namespace sdl_platformer
{
   Physics::Physics()
      : m_velocity_x(0), m_velocity_y(0),
        m_acceleration_x(1.30), m_acceleration_y(1),
        m_gravity_enabled(true), m_gravity_modifier( 0.2f ),
        m_speed_limit(4), m_fly_mode(false)
   {
   }

   Physics::~Physics()
   {
   }

   void
   Physics::reset()
   {
      set_velocity_x(0.0f);
      set_velocity_y(0.0f);

      set_acceleration_x(0.0f);
      set_acceleration_y(0.0f);

      set_gravity_enabled(true);
      set_gravity_modifier(1.0f);
   }

   void
   Physics::set_velocity_x(float new_vel_x) { m_velocity_x = new_vel_x; }

   void
   Physics::set_velocity_y(float new_vel_y) { m_velocity_y = new_vel_y; }

   float
   Physics::get_velocity_x() const { return m_velocity_x; }

   float
   Physics::get_velocity_y() const { return m_velocity_y; }

   void
   Physics::set_acceleration_x(float new_acc_x) { m_acceleration_x = new_acc_x; }

   void
   Physics::set_acceleration_y(float new_acc_y) { m_acceleration_y = new_acc_y; }

   float
   Physics::get_acceleration_x() const { return m_acceleration_x; }

   float
   Physics::get_acceleration_y() const { return m_acceleration_y; }

   void
   Physics::set_gravity_enabled(bool gravity_enabled)
   {
      if( !m_fly_mode )
      {
         m_gravity_enabled = gravity_enabled;
      }
   }

   bool
   Physics::get_gravity_enabled() const { return m_gravity_enabled; }

   void
   Physics::set_gravity_modifier(float new_modifier)
   {
      m_gravity_modifier = new_modifier;
   }

   float
   Physics::get_gravity_modifier() const { return m_gravity_modifier; }

   void
   Physics::move_left(float elapsed_time)
   {
      if( m_velocity_x > -1 )
      {
         m_velocity_x -= 30 * m_acceleration_x * elapsed_time;
      }
      else
      {
         m_velocity_x *= 10 * elapsed_time * m_acceleration_x + 1;
      }
   }

   void
   Physics::move_right(float elapsed_time)
   {
      if( m_velocity_x < 1 )
      {
         m_velocity_x += 30 *m_acceleration_x * elapsed_time;
      }
      else
      {
         m_velocity_x *= 10 * elapsed_time * m_acceleration_x + 1;
      }
   }

   void
   Physics::move_up(float elapsed_time)
   {
      if( m_velocity_y > -1 )
      {
         m_velocity_y -= 30 * m_acceleration_x * elapsed_time;
      }
      else
      {
         m_velocity_y *= 10 * elapsed_time * m_acceleration_x + 1;
      }
   }

   void
   Physics::move_down(float elapsed_time)
   {
      if( m_velocity_y < 1 )
      {
         m_velocity_y += 30 *m_acceleration_x * elapsed_time;
      }
      else
      {
         m_velocity_y *= 10 * elapsed_time * m_acceleration_x + 1;
      }
   }
   void
   Physics::speed_left(float elapsed_time)
   {
      if( m_velocity_x > -1 )
      {
         m_velocity_x -= 1;
      }
      else
      {
         m_velocity_x *= 20 * elapsed_time * m_acceleration_x + 1;
      }
   }

   void
   Physics::speed_right(float elapsed_time)
   {
      if( m_velocity_x < 1 )
      {
         m_velocity_x += 1;
      }
      else
      {
         m_velocity_x *= 20 * elapsed_time * m_acceleration_x + 1;
      }
   }

   void
   Physics::jump()
   {
      m_velocity_y -= m_acceleration_y * 8;
   }

   void
   Physics::stop_motion_at(float speed)
   {
      if( abs(m_velocity_x) < speed )
      {
         m_velocity_x = 0;
      }
   }

   void
   Physics::cap_x_velocity(float speed_limit)
   {
      if( m_velocity_x > speed_limit )
      {
         m_velocity_x = speed_limit;
      }
      else if( m_velocity_x < -speed_limit )
      {
         m_velocity_x = -speed_limit;
      }
   }

   void
   Physics::handle_fly_mode(float elapsed_time)
   {
      if( m_fly_mode )
      {
         cap_x_velocity( m_speed_limit * 1.5 );
         if( m_velocity_y > m_speed_limit * 1.5 )
         {
            m_velocity_y = m_speed_limit;
         }
         else if( m_velocity_y < -m_speed_limit * 1.5 )
         {
            m_velocity_y = -m_speed_limit;
         }
         m_velocity_y *= World::current()->get_friction_modifier();
         float padding = 1;
         if( m_velocity_y >= 0 - padding)
         {
            move_down( std::fmax(elapsed_time / 6, 0.0001) );
         }
      }
   }
   void
   Physics::update(float elapsed_time)
   {
      World * cur = World::current();
      stop_motion_at(0.1f);
      if( !m_fly_mode)
      {
         cap_x_velocity(m_speed_limit);
      }

      handle_fly_mode(elapsed_time);

      //apply friction
      m_velocity_x *= cur->get_friction_modifier();
      //std::cout << m_velocity_x << "\n";

      //apply gravity if needed
      if( m_gravity_enabled )
      {
         m_velocity_y += m_gravity_modifier * m_acceleration_y;
      }
   }

   void
   Physics::enable_fly_mode()
   {
      m_fly_mode = true;
   }

   void
   Physics::disable_fly_mode()
   {
      m_fly_mode = false;
   }

}// sdl_platformer
