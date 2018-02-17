#ifndef _CONNECTION_
#define _CONNECTION_

#include <string>

#include "current.h"

namespace sdl_platform
{
   class Connection : Current<Network>
   {
      private:
         std::string m_ip;
         int m_port;
         bool m_connected;
         boost::asio::ioservice & m_io_service;
         tcp::socket m_socket;

      public:
         Connection(std::string ip, int port);
         ~Connection();

         bool connect();
   };
}
#endif //_CONNECTION_
