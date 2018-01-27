#ifndef _COLLISION_HIT_
#define _COLLISION_HIT_
namespace sdl_platformer
{
   class CollisionHit
   {
      public:
         CollisionHit();
         ~CollisionHit();

         bool m_left, m_right;
         bool m_top, m_bottom;
         bool m_crush;
   };
} // namepsace sdl_platformer
#endif // _COLLISION_HIT_
