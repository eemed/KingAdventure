#ifndef _SCREEN_MANAGER_
#define _SCREEN_MANAGER_

#include "screen.h"
#include "render_context.h"

namespace sdl_platformer
{
   class ScreenManager
   {
      private:
         Screen m_screen;

      public:
         ScreenManager();
         ~ScreenManager();

         void draw( RenderContext & ) const;
         void resize(int width, int height);
   };
} // namespace sdl_platformer
#endif // _SCREEN_MANAGER_
