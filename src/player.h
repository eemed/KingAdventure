#ifndef _PLAYER_
#define _PLAYER_

#include <string>

#include "SDL2/SDL.h"
#include "rectangle.h"
#include "physics.h"
#include "collision_vector.h"
#include "screen.h"
#include "player_state.h"
#include "sprite_manager.h"

namespace sdl_platformer
{
   class Player
   {
      private:
         Rectangle m_hitbox;
         Physics m_physics;

         PlayerState m_state;
         SpriteManager m_sprite_manager;
         SDL_Rect m_dest;

      public:
         Player(int x, int y,
               int width, int height, Color col, std::string name, char_type t);
         ~Player();

         std::string get_name() const;

         bool hits_ground() const;
         void hits_ground(bool n_hit);
         jump_state get_jump_state() const;

         void update(float elapsed_time);
         void set_jump_state();

         void move_right(float elapsed_time);
         void move_left(float elapsed_time);

         void move_up(float elapsed_time);
         void move_down(float elapsed_time);

         void speed_right(float elapsed_time);
         void speed_left(float elapsed_time);
         void toggle_gravity();

         void jump();

         void fix_collision();
         void draw() const;
         void f_move(float dx, float dy);
         void update_facing();

         int get_x() const;
         int get_y() const;
   };
} // namespace sdl_platformer
#endif // _PLAYER_
