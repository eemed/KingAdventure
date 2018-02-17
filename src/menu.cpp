#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#include "generator.h"

#include "menu.h"
#include "screen.h"
#include "sprite_manager.h"
#include "game.h"

namespace sdl_platformer
{
   TTF_Font * setup_ttf(const std::string &font_name);

   Menu::Menu( std::vector< std::string > n_items )
      : m_selected( 0 ),
      m_menu_items( n_items ),
      m_text_color( Color(150, 150, 150, 255) ),
      m_selected_color( Color() ),
      m_background_color( Color(20, 20, 20, 255) ),
      m_ctx( RenderContext() )
   {
      activate();
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "/build/apps/res/fonts/cryonix.ttf";
      m_font = setup_ttf( p.make_preferred().string().c_str() );
      update_textures();
   }

   Menu::~Menu()
   {
      deactivate();
   }

   void
   Menu::update()
   {
      update_textures();
   }
   void
   Menu::select()
   {
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "/build/apps/res/worlds/";
      std::string world_name;
      switch( m_selected )
      {
         case 0:
            world_name = generate_world(1024, 70);
            Game::current()->create_world(
                  (p.make_preferred().string() + world_name).c_str() );
            Game::current()->destroy_menu();
            break;
        case 1:
            Game::current()->terminate();
            break;
        default:
            break;
      }
   }

   void
   Menu::move_up()
   {
      if( m_selected > 0 )
      {
         m_selected -= 1;
      }
   }

   void
   Menu::move_down()
   {
      if( m_selected < m_menu_items.size() - 1 )
      {
         m_selected += 1;
      }
   }

   void
   Menu::draw()
   {
      Screen::current()->draw( m_ctx );
   }

   void Menu::set_background_color( Color col) { m_background_color = col; }
   void Menu::set_selected_color( Color col) { m_selected_color = col; }
   void Menu::set_text_color( Color col) { m_text_color = col; }

   Color Menu::get_background_color( Color ) const { return m_background_color; }
   Color Menu::get_selected_color( Color ) const { return m_selected_color; }
   Color Menu::get_text_color( Color ) const { return m_text_color; }

   bool
   Menu::update_textures()
   {
      int old_y = 0;
      std::vector< std::pair< SDL_Rect, SDL_Texture *> > new_textures;
      for(std::vector< std::string >::size_type i = 0; i < m_menu_items.size(); ++i)
      {
         SDL_Rect rect;
         SDL_Surface* surface;
         SDL_Texture * texture;
         if( m_selected == i )
         {
            //make with selected color
            surface = TTF_RenderText_Shaded(
                   m_font,
                   m_menu_items[i].c_str(),
                   m_selected_color.get_sdl_color(),
                   m_background_color.get_sdl_color() );
         }
         else
         {
            //Make with default color
            surface = TTF_RenderText_Shaded(
                   m_font,
                   m_menu_items[i].c_str(),
                   m_text_color.get_sdl_color(),
                   m_background_color.get_sdl_color() );
         }
         texture = texture_from_surface( surface );
         SDL_QueryTexture(
               texture,
               NULL,
               NULL,
               &rect.w,
               &rect.h );

         //SPACING OF TEXTS
         //
         rect.x = Screen::current()->get_width() / 2 - rect.w / 2;
         rect.y = Screen::current()->get_height() / 4 + old_y;
         new_textures.push_back(
               std::pair< SDL_Rect, SDL_Texture *>( rect, texture));
         old_y = rect.h;
      }
      m_ctx.m_text = new_textures;
      //std::cout << "Made textures\n";
      return true;
   }

    TTF_Font *
    setup_ttf( const std::string &font_name )
    {
        if( TTF_Init() == -1 )
        {
            std::cout << " Failed to init TTF: " << SDL_GetError() << std::endl;
            return NULL;
        }

        TTF_Font * font = TTF_OpenFont( font_name.c_str(), 24);

        if ( font == nullptr )
        {
            std::cout << " Failed to laod font: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return font;
    }
}// sdl_platformer
