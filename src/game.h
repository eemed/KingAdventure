#ifndef _GAME_
#define _GAME_

#include <string>

#include "world.h"
#include "screen.h"
#include "menu.h"
#include "input_handler.h"
#include "current.h"

namespace sdl_platformer
{
   class Game : public Current<Game>
   {
      private:
         Screen m_screen;
         Menu m_menu;
         World m_world;
         InputHandler m_input;
         bool m_running;

      public:
         Game(std::string filename);
         ~Game();

         void run();
         void terminate();

         //void activate();
         //void deactivate();
   };
} // sdl_platformer
#endif // _GAME_
