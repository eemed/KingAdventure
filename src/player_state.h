#ifndef _PLAYER_STATE_
#define _PLAYER_STATE_

#include <string>

namespace sdl_platformer
{
   enum jump_state
   {
      NOT_JUMPING, RISE, TOP, FALL, LAND
   };

   enum facing
   {
      RIGHT, LEFT, UP, DOWN
   };

   class PlayerState
   {
      public:
        PlayerState(std::string name, jump_state n_state,
                    bool fly, bool on_ground, facing n_faceing);

        std::string m_name;
        jump_state m_jump_state;
        bool m_fly_mode;
        bool m_on_ground;
        facing m_facing;
   };
}
#endif // _PLAYER_STATE_
