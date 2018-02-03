#include <boost/filesystem.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "sprite_factory.h"

namespace sdl_platformer
{
   SpriteFactory::SpriteFactory()
   {
      IMG_Init(IMG_INIT_PNG);
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "build/apps/res/sprites/sheet.png";
      std::cout << p.string() << std::endl;
      SDL_Surface * environment =
         IMG_Load( p.make_preferred().string().c_str() );
      m_texture = texture_from_surface(environment);
      SDL_FreeSurface( environment );
      activate();
   }

   SpriteFactory::~SpriteFactory()
   {
      deactivate();
      SDL_DestroyTexture( m_texture );
   }

   SDL_Rect
   SpriteFactory::get_sprite(std::string type)
   {
      if( type == "tree" )
      {
         m_source.x = 2 * 16;
         m_source.y = 0;
         m_source.w = 5 * 16;
         m_source.h = 8 * 16;
      }
      else if( type == "vine_roof" )
      {
         m_source.x = 1;
         m_source.y = 1;
         m_source.w = 2*16;
         m_source.h = 2*16;
      }
      else if( type == "water_top" )
      {
         m_source.x = 8 * 16;
         m_source.y = 5 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_grass_left" )
      {
         m_source.x = 7 * 16;
         m_source.y = 0;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_in_rock" )
      {
         m_source.x = 7 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_grass_right" )
      {
         m_source.x = 9 * 16;
         m_source.y = 0;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_grass" )
      {
         m_source.x = 8 * 16;
         m_source.y = 0;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_grass_corner_left" )
      {
         m_source.x = 8 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_grass_corner_right" )
      {
         m_source.x = 9 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_corner_right" )
      {
         m_source.x = 12 * 16;
         m_source.y = 0 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground" )
      {
         m_source.x = 12 * 16;
         m_source.y = 0;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_wall_right" )
      {
         m_source.x = 12 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_wall_left" )
      {
         m_source.x = 10 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "ground_in" )
      {
         m_source.x = 11 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "sign_dark_arrow" )
      {
         m_source.x = 15 * 16;
         m_source.y = 1 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "box" )
      {
         m_source.x = 8 * 16;
         m_source.y = 4 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_rose" )
      {
         m_source.x = 9 * 16;
         m_source.y = 4 * 16;
         m_source.w = 32;
         m_source.h = 32;
      }
      else if( type == "back_plant1" )
      {
         m_source.x = 9 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_plant2" )
      {
         m_source.x = 10 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "water_deep" )
      {
         m_source.x = 8 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_hk" )
      {
         m_source.x = 11 * 16;
         m_source.y = 4 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_up" )
      {
         m_source.x = 12 * 16;
         m_source.y = 4 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_in" )
      {
         m_source.x = 12 * 16;
         m_source.y = 5 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_kl" )
      {
         m_source.x = 13 * 16;
         m_source.y = 4 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_right" )
      {
         m_source.x = 13 * 16;
         m_source.y = 5 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_left_down" )
      {
         m_source.x = 11 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_down" )
      {
         m_source.x = 12 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_right_down" )
      {
         m_source.x = 13 * 16;
         m_source.y = 6 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      else if( type == "back_left" )
      {
         m_source.x = 11 * 16;
         m_source.y = 5 * 16;
         m_source.w = 16;
         m_source.h = 16;
      }
      return m_source;
   }

   SDL_Texture *
   SpriteFactory::get_texture() const
   {
      return m_texture;
   }
} // sdl_platformer
