#ifndef _GAME_
#define _GAME_

#include <string>

#include "world.h"
#include "screen_manager.h"
#include "menu.h"
#include "input_handler.h"
#include "current.h"
#include "sprite_factory.h"
#include "network.h"

namespace sdl_platformer
{
   class Game : public Current<Game>
   {
      private:
         ScreenManager m_screen_manager;
         SpriteFactory m_factory;
         Menu * m_menu;
         World * m_world;
         Network * m_network;
         InputHandler m_input;
         bool m_running;

      public:
         Game();
         ~Game();

         void run();
         void terminate();
         void update(float dt);
         void render();
         void create_world(std::string filename);

         void destroy_menu();
         Menu * get_menu();
   };
} // sdl_platformer
#endif // _GAME_
