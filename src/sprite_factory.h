#ifndef _SPRITE_FACTORY_
#define _SPRITE_FACTORY_

#include <string>

#include "sprite_manager.h" // for enums

namespace sdl_platformer
{
   class SpriteFactory
   {
      public:
         SpriteFactory();
         ~SpriteFactory();

         std::pair< SDL_Rect, SDL_Texture *> get_sprite(sprite_type type);
         std::pair< SDL_Rect, SDL_Texture *> get_sprite(std::string type); //type as string
         std::pair< SDL_Rect, SDL_Texture *> get_sprite(int x, int y, int w, int h);
   };
} // sdl_platformer
#endif
