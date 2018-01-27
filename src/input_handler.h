#ifndef _INPUT_HANDLER_
#define _INPUT_HANDLER_

#include <SDL2/SDL.h>

namespace sdl_platformer
{
   class InputHandler
   {
      private:

         const Uint8 * m_keyboard;
         void update_events();
         void process_menu_events();
         void process_player_events(const float & elapsed_time);

         static InputHandler * _current;

      public:

         InputHandler();
         ~InputHandler();

         void process_events(const float & elapsed_time);
         static InputHandler * current();

         void activate();
         void deactivate();
   };
} // namespace sdl_platformer
#endif //_INPUT_HANDLER_
