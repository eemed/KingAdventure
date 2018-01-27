#ifndef _MENU_
#define _MENU_

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "color.h"

namespace sdl_platformer
{
   class Menu
   {
      protected:

         unsigned int m_selected;
         std::vector< std::string > m_menu_items;
         Color m_text_color;
         Color m_selected_color;
         Color m_background_color;

         void create_textures(std::vector< std::string > text_items);

         static Menu * _current;

      public:

         Menu( std::vector< std::string > menu_items);
         ~Menu();

         unsigned int select() const;

         void move_up();
         void move_down();

         void draw() const;

         void set_background_color( Color );
         void set_selected_color( Color );
         void set_text_color( Color );

         Color get_background_color( Color ) const;
         Color get_selected_color( Color ) const;
         Color get_text_color( Color ) const;

         static Menu * current();

         void activate();
         void deactivate();
   };
} // sdl_platformer
#endif //_MENU_
