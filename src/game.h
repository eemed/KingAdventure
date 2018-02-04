#ifndef _GAME_
#define _GAME_

#include <string>

#include "world.h"
#include "screen_manager.h"
#include "menu.h"
#include "input_handler.h"
#include "current.h"
#include "sprite_factory.h"

namespace sdl_platformer
{
   class Game : public Current<Game>
   {
      private:
         ScreenManager m_screen_manager;
         SpriteFactory m_factory;
         Menu m_menu;
         World m_world;
         InputHandler m_input;
         bool m_running;

      public:
         Game(std::string filename);
         ~Game();

         void run();
         void terminate();
   };
} // sdl_platformer
#endif // _GAME_
