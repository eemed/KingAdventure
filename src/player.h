#ifndef _PLAYER_
#define _PLAYER_

#include <string>

#include "rectangle.h"
#include "physics.h"
#include "collision_vector.h"

namespace sdl_platformer
{
   enum jump_state
   {
      NOT_JUMPING, RISE, TOP, FALL
   };

   class Player
   {
      private:

         Rectangle m_hitbox;
         Physics m_physics;

         std::string m_name;

         bool m_on_ground;
         jump_state m_jump_state;

      public:

         Player(int x, int y,
               int width, int height, Color col, std::string name);

         std::string get_name() const;

         bool hits_ground() const;
         void hits_ground(bool n_hit);
         jump_state get_jump_state() const;

         void update(float elapsed_time);
         void set_jump_state();

         void move_right(float elapsed_time);
         void move_left(float elapsed_time);

         void speed_right(float elapsed_time);
         void speed_left(float elapsed_time);

         void jump();

         void fix_collision();
         void draw() const;
   };
} // namespace sdl_platformer
#endif // _PLAYER_
