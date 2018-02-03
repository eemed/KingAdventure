#ifndef _SPRITE_MANAGER_
#define _SPRITE_MANAGER_

#include <utility>
#include <map>
#include <string>

#include "SDL2/SDL.h"

namespace sdl_platformer
{
   enum char_type
   {
      BOY = 0, KING = 1, SOLDIER = 2
   };

   enum sprite_type
   {
      NONE, IDLE, JUMP_RISE, JUMP_LAND, JUMP_FALL , RUN, WALK,
      WALL, GROUND, TREE, BOX, WATER
   };

   class SpriteManager
   {
      private:
         std::pair<sprite_type, int> m_last_player;
         SDL_Texture * m_chars;
         SDL_Rect m_source_player;
         float m_animation_speed_acc;

      public:
         SpriteManager( char_type type);
         ~SpriteManager();

         bool load_sprites();
         void update_player(sprite_type, float elapsed_time);
         void force_update_player(sprite_type);
         std::pair< SDL_Rect , SDL_Texture *> get_player() const;
   };

   SDL_Texture * texture_from_surface(SDL_Surface *);
} // sdl_platfromer
#endif // _SPRITE_MANAGER_
