#include <iostream>
#include <cstdlib>

#include "physics.h"
#include "world.h"
#include "collision.h"
#include "current.h"

namespace sdl_platformer
{
   Physics::Physics()
      : m_velocity_x(0), m_velocity_y(0),
        m_acceleration_x(50), m_acceleration_y(1),
        m_gravity_enabled(true), m_gravity_modifier( 0.2f ),
        m_speed_limit(8)
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
      m_gravity_enabled = gravity_enabled;
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
      m_velocity_x += -(elapsed_time * m_acceleration_x);
      m_speed_limit = 6;
   }

   void
   Physics::move_right(float elapsed_time)
   {
      m_velocity_x += elapsed_time * m_acceleration_x;
      m_speed_limit = 6;
   }

   void
   Physics::speed_left(float elapsed_time)
   {
      m_velocity_x += -(elapsed_time * m_acceleration_x);
      m_speed_limit = 10;
   }

   void
   Physics::speed_right(float elapsed_time)
   {
      m_velocity_x += elapsed_time * m_acceleration_x;
      m_speed_limit = 10;
   }

   void
   Physics::jump()
   {
      m_velocity_y -= m_acceleration_y * 8;
   }

   void
   Physics::update(float elapsed_time)
   {
      World * cur = World::current();
      if( abs(m_velocity_x) < 0.1f )
      {
         m_velocity_x = 0;
      }
      if( m_velocity_x > m_speed_limit )
      {
         m_velocity_x = m_speed_limit;
      }
      else if( m_velocity_x < -m_speed_limit )
      {
         m_velocity_x = -m_speed_limit;
      }

      //apply friction
      m_velocity_x -= m_velocity_x * cur->get_friction_modifier();

      //apply gravity if needed
      if( m_gravity_enabled and !cur->get_player().hits_ground())
      {
         m_velocity_y += m_gravity_modifier * m_acceleration_y;
      }
      if(elapsed_time > 100 )
      {
         m_velocity_x = 0;
      }
   }

}// sdl_platformer
