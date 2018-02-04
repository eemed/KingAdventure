#include <iostream>
#include <boost/filesystem.hpp>

#include "sprite_manager.h"
#include "screen.h" // for renderer
#include "SDL2/SDL_image.h" // IMG

namespace sdl_platformer
{
   SpriteManager::SpriteManager( char_type t)
      : m_animation_speed_acc(0)
   {
      //Init images
      IMG_Init(IMG_INIT_PNG);

      m_source_player.w = 32;
      m_source_player.h = 32;
      m_source_player.y = 32 * t;
      m_source_player.x = 0;

      m_last_player.first = NONE;
      m_last_player.second = 0;

      if( !load_sprites() )
      {
         std::cout << "Couldn't load spites.\n";
      }
   }

   SpriteManager::~SpriteManager()
   {
      SDL_DestroyTexture(m_chars);
      //SDL_DestroyTexture(m_env);
   }

   bool
   SpriteManager::load_sprites()
   {
      //std::cout << "LoadSprites\n";
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "build/apps/res/sprites/characters.png";
      SDL_Surface * characters =
         IMG_Load( p.make_preferred().string().c_str() );
      m_chars = texture_from_surface(characters);
      SDL_FreeSurface( characters );
      //std::cout << "Loaded sprites\n";
      return true;
   }

   void
   SpriteManager::update_player(sprite_type type, float elapsed_time)
   {
      m_animation_speed_acc += elapsed_time;
      if( m_animation_speed_acc > 0.1)
      {
         int pos_num = 0;
         switch( type )
         {
            case WALK:
               if( m_last_player.first == WALK )
               {
                  pos_num = (m_last_player.second + 1) % 4;
               }
               m_source_player.x = pos_num * 32;
               m_last_player.second = pos_num;
               break;
            case JUMP_RISE:
               m_source_player.x = 5 * 32;
               break;
            case JUMP_FALL:
               m_source_player.x = 6 * 32;
               break;

            default:
               //Return old position if spritetype cant be found
               break;
         }
         m_last_player.first = type;
         m_animation_speed_acc = 0;
      }
   }

   void
   SpriteManager::force_update_player(sprite_type type)
   {
      int pos_num = 0;
      m_animation_speed_acc = 0;
      switch( type )
      {
         case WALK:
            if( m_last_player.first == WALK )
            {
               pos_num = (m_last_player.second + 1) % 4;
            }
            m_source_player.x = pos_num * 32;
            m_last_player.second = pos_num;
            break;
         case JUMP_RISE:
            m_source_player.x = 5 * 32;
            break;
         case JUMP_FALL:
            m_source_player.x = 6 * 32;
            break;
         case IDLE:
            m_source_player.x = 0;

         default:
            //Return old position if spritetype cant be found
            break;
      }
      m_last_player.first = type;
      m_animation_speed_acc = 0;
   }
   std::pair< SDL_Rect , SDL_Texture *>
   SpriteManager::get_player() const
   {
      SDL_Rect a = m_source_player;
      return std::pair< SDL_Rect , SDL_Texture *> (a, m_chars);
   }

   SDL_Texture *
   texture_from_surface(SDL_Surface * surface)
   {
      //std::cout << "Creating Texture\n";
      //Magenta is transparent
      SDL_SetColorKey( surface,
            SDL_TRUE, SDL_MapRGB( surface->format, 255, 0 ,255) );

      //Get current screen renderer and make surface
      SDL_Texture * tex = SDL_CreateTextureFromSurface(
            Screen::current()->get_renderer(), surface);
      //std::cout << "Created Texture\n" << tex << "\n";
      return tex;
   }

} // sdl_platformer
