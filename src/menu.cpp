#include "menu.h"
#include "screen.h"

namespace sdl_platformer
{

   Menu * Menu::_current = NULL;


   Menu::Menu( std::vector< std::string > n_items )
      : m_selected( n_items.size() ),
      m_menu_items( n_items ),
      m_text_color( Color(150, 150, 150, 255) ),
      m_selected_color( Color() ),
      m_background_color( Color(20, 20, 20, 255) )
   {
      activate();
   }

   Menu::~Menu()
   {
      deactivate();
   }

   unsigned int
   Menu::select() const { return m_selected; }

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
   Menu::draw() const
   {
      return;
   }

   void Menu::set_background_color( Color col) { m_background_color = col; }
   void Menu::set_selected_color( Color col) { m_selected_color = col; }
   void Menu::set_text_color( Color col) { m_text_color = col; }

   Color Menu::get_background_color( Color ) const { return m_background_color; }
   Color Menu::get_selected_color( Color ) const { return m_selected_color; }
   Color Menu::get_text_color( Color ) const { return m_text_color; }

   Menu *
   Menu::current() { return _current; }

   void
   Menu::activate() { _current = this; }

   void
   Menu::deactivate() { _current = NULL; }
}// sdl_platformer
