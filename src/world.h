#ifndef _WORLD_
#define _WORLD_

#include <string>

#include "player.h"
#include "render_context.h"

namespace sdl_platformer
{
   class World
   {
      private:

         static World * _current;

         RenderContext m_render_context;
         Player m_player;
         float m_friction_modifier;

      public:

         World(std::string filename);
         ~World();

         //Moves render context to center player
         //void center_player();

         Player & get_player();

         static World * current();
         void activate();
         void deactivate();

         void update();

         float get_friction_modifier() const;
         RenderContext * get_render_context();
   };
}
#endif //_WORLD_
