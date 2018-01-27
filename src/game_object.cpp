#include "game_object.h"

namespace sdl_platformer
{
   GameObject::GameObject(int pos_x, int pos_y, Color color)
      : m_pos_x( pos_x ),
        m_pos_y( pos_y ),
        m_color( color )
   {
   }

   GameObject::~GameObject()
   {
   }

   int
   GameObject::get_x() const { return m_pos_x; }

   int
   GameObject::get_y() const { return m_pos_y; }

   Color
   GameObject::get_color() const { return m_color; }

   void
   GameObject::set_x(int new_x) { m_pos_x = new_x; }

   void
   GameObject::set_y(int new_y) { m_pos_y = new_y; }

   void
   GameObject::set_color(Color new_color) { m_color = new_color; }

}// sdl_platformer
