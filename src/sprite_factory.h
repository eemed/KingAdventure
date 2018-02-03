#ifndef _SPRITE_FACTORY_
#define _SPRITE_FACTORY_

#include <SDL2/SDL.h>
#include <utility>
#include <string>

#include "current.h"
#include "sprite_manager.h" // for enums

namespace sdl_platformer
{
   class SpriteFactory : public Current<SpriteFactory>
   {
      private:
         SDL_Rect m_source;
         SDL_Texture * m_texture;
      public:
         SpriteFactory();
         ~SpriteFactory();

         //std::pair< SDL_Rect, SDL_Texture *> get_sprite(sprite_type type);
         SDL_Rect get_sprite(std::string type); //type as string
         SDL_Texture * get_texture() const;
         //std::pair< SDL_Rect, SDL_Texture *> get_sprite(int x, int y, int w, int h);
   };
} // sdl_platformer
#endif
