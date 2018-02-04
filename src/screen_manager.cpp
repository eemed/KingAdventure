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
   ScreenManager::scroll_by_player(int plus_x, int minus_x, int plus_y, int minus_y)
   {
      if( World::current() != 0 )
      {
         Player * p = World::current()->get_player();
         RenderContext * ctx = World::current()->get_render_context();
         int player_max = p->get_x() + plus_x;
         int player_min = p->get_x() - minus_x;
         int player_max_y = p->get_y() + plus_y;
         int player_min_y = p->get_y() - minus_y;

         //--------
         if( player_max > m_screen.get_width() )
         {
            ctx->move( -(player_max - m_screen.get_width() ), 0);
            p->f_move( -(player_max - m_screen.get_width() ), 0);
         }

         if( player_min < 0 )
         {
            ctx->move( minus_x - p->get_x() , 0);
            p->f_move( minus_x - p->get_x(), 0);
         }

         if( player_max_y > m_screen.get_height() )
         {
            ctx->move( 0 , -(player_max_y - m_screen.get_height() ) );
            p->f_move( 0 , -(player_max_y - m_screen.get_height() ) );
         }

         if( player_min_y < 0 )
         {
            ctx->move( 0, minus_y - p->get_y() );
            p->f_move( 0, minus_y - p->get_y() );
         }
      }
   }
}// sdl_platformer
