#include "world.h"

namespace sdl_platformer
{
   //World * World::_current = 0;

   World::World(std::string filename)
      : m_render_context( RenderContext(filename) ),
        m_player( Player(35, 35, 30, 30, Color(255, 0, 0, 255), "Jonne") ),
        m_friction_modifier(0.1f)
   {
      activate();
   }

   World::~World()
   {
      deactivate();
      //Delete stuff
   }

   void
   World::update(float elapsed_time)
   {
      m_player.update(elapsed_time);
   }

   Player &
   World::get_player() { return m_player; }

   //World *
   //World::current() { return _current; }

   //void
   //World::activate() { _current = this; }

   //void
   //World::deactivate() { _current = NULL; }

   float
   World::get_friction_modifier() const { return m_friction_modifier; }

   RenderContext *
   World::get_render_context()
   {
      return &m_render_context;
   }

} // sdl_platformer
