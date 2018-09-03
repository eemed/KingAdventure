#ifndef _NETWORK_
#define _NETWORK_

#include <string>

#include "connection.h"

namespace sdl_platformer
{
   class Network
   {
      private:
         boost::shared_ptr< boost::asio::io_service > m_io_service;
         bool m_connected;
         Connection * m_curr_conn;
         boost::thread_group m_threads;

      public:
         Network();
         ~Network();

         bool connect_to(std::string ip, std::string port);
         bool disconnect();
         bool send_message(std::string msg);
         void create_thread( boost::shared_ptr< boost::asio::io_service > m_io_service);
         //bool send_location_data(Player p);
   };
} // sdl_platformer
#endif //_NETWORK_
