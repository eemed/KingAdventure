#ifndef _NETWORK_
#define _NETWORK_

#include <string>

#include "current.h"

namespace sdl_platformer
{
   class Network : Current<Network>
   {
      private:
         bool connected;
         std::string ip;
         int port;

      public:
         Network();
         ~Network();

         bool connect_to(std::string ip, int port);
         bool disconnect();
         bool send_message(std::string msg);
         bool send_location_data(Player p);
   };
} // sdl_platformer
#endif //_NETWORK_
