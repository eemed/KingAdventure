#ifndef _GAME_
#define _GAME_

#include <string>

#include "world.h"
#include "screen.h"
#include "menu.h"
#include "input_handler.h"

namespace sdl_platformer
{
   class Game
   {
      private:

         Screen m_screen;
         Menu m_menu;
         World m_world;
         InputHandler m_input;
         bool m_running;

         static Game * _current;

      public:
         Game(std::string filename);
         ~Game();

         void run();
         void terminate();

         static Game * current();

         void activate();
         void deactivate();
   };
} // sdl_platformer
#endif // _GAME_
