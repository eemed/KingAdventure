#ifndef _SCREEN_MANAGER_
#define _SCREEN_MANAGER_

#include "screen.h"
#include "render_context.h"
#include "player.h"
#include "current.h"

namespace sdl_platformer
{
   class ScreenManager : public Current<ScreenManager>
   {
      public:
         Screen m_screen;
         ScreenManager();
         ~ScreenManager();

         void draw( RenderContext & ) const;
         void scroll_by_player(int plus_x, int minus_x, int plus_y, int minus_y);
   };
} // namespace sdl_platformer
#endif // _SCREEN_MANAGER_
