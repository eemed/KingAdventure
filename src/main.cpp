#include <iostream>
#include <boost/filesystem.hpp>
#include "game.h"
   bool
   init_sdl()
   {
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
      {
          std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
          return false;
      }
      return true;
   }

int main()
{
   boost::filesystem::path p = boost::filesystem::current_path();
   p /= "/build/apps/res/worlds/world.json";
   init_sdl();
   sdl_platformer::Game game( p.make_preferred().string().c_str());
   game.run();
   return 0;
}
