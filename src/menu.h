#ifndef _MENU_
#define _MENU_

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "color.h"
#include "current.h"
#include "render_context.h"

namespace sdl_platformer
{
   class Menu : public Current<Menu>
   {
      protected:
         unsigned int m_selected;
         std::vector< std::string > m_menu_items;
         Color m_text_color;
         Color m_selected_color;
         Color m_background_color;
         TTF_Font * m_font;
         RenderContext m_ctx;

         void create_textures(std::vector< std::string > text_items);

      public:
         Menu( std::vector< std::string > menu_items);
         ~Menu();

         void select();

         void move_up();
         void move_down();

         void draw();

         void set_background_color( Color );
         void set_selected_color( Color );
         void set_text_color( Color );

         Color get_background_color( Color ) const;
         Color get_selected_color( Color ) const;
         Color get_text_color( Color ) const;

         bool update_textures();
         void update();
   };
} // sdl_platformer
#endif //_MENU_
