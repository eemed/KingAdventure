#ifndef _PHYSICS_
#define _PHYSICS_

namespace sdl_platformer
{
   class Physics
   {
      protected:

         float m_velocity_x;
         float m_velocity_y;

         float m_acceleration_x;
         float m_acceleration_y;

         bool m_gravity_enabled;
         float m_gravity_modifier;
         float m_speed_limit;
         bool m_lock;

      public:
         Physics();
         ~Physics();

         void reset();

         void set_velocity_x(float new_vel_x);
         void set_velocity_y(float new_vel_x);

         float get_velocity_x() const;
         float get_velocity_y() const;

         void set_acceleration_x(float new_acc_x);
         void set_acceleration_y(float new_acc_y);

         float get_acceleration_x() const;
         float get_acceleration_y() const;

         void set_gravity_enabled(bool gravity_enabled);
         bool get_gravity_enabled() const;

         void set_gravity_modifier(float new_modifier);
         float get_gravity_modifier() const;

         void move_left(float elapsed_time);
         void move_right(float elapsed_time);

         void move_up(float elapsed_time);
         void move_down(float elapsed_time);

         void speed_left(float elapsed_time);
         void speed_right(float elapsed_time);

         void jump();
         void update(float elapsed_time);

         void lock_gravity();
         void unlock_gravity();
   };
} // namespace sdl_platformer
#endif //_PHYSICS_
