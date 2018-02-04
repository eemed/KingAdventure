#include <iostream>

#include "screen_manager.h"
#include "world.h"

namespace sdl_platformer
{
   ScreenManager::ScreenManager()
      : m_screen( Screen() )
   {
      activate();
   }

   ScreenManager::~ScreenManager()
   {
      deactivate();
   }

   void
   ScreenManager::draw( RenderContext & r_ctx) const
   {
      m_screen.draw( r_ctx );
   }

   void
   ScreenManager::scroll_by_player(int padding)
   {
      if( World::current() != 0 )
      {
         Player * p = World::current()->get_player();
         RenderContext * ctx = World::current()->get_render_context();
         int player_max = p->get_x() + padding;
         int player_min = p->get_x() - padding;
         std::cout << "p_max: " << player_max;
         std::cout << "p_min: " << player_min << "\n";

         if( player_max >= m_screen.get_width() )
         {
            std::cout << "over: " << "\n";
            ctx->move( -(player_max - m_screen.get_width() ), 0);
            p->f_move( -(player_max - m_screen.get_width() ), 0);
         }

         if( player_min <= 0 )
         {
            std::cout << "under: " << "\n";
            ctx->move( padding - p->get_x() , 0);
            p->f_move( padding - p->get_x(), 0);
         }
      }
   }
}// sdl_platformer
