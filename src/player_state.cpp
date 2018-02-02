#include "player_state.h"

namespace sdl_platformer
{
   PlayerState::PlayerState(std::string name,
                            jump_state  n_state,
                            bool fly_mode,
                            bool on_ground,
                            facing n_facing )
      : m_name( name ),
        m_jump_state( n_state ),
        m_fly_mode( fly_mode ),
        m_on_ground( on_ground ),
        m_facing( n_facing )
   {
   }
} // sdl_platformer
