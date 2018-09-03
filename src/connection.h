#ifndef _CONNECTION_
#define _CONNECTION_

#include <boost/system/system_error.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "deque.h"
#include "packet.h"

namespace sdl_platformer
{
   class Connection
   {
      private:
         boost::shared_ptr< boost::asio::io_service > m_io_service;
         boost::shared_ptr< boost::asio::ip::tcp::socket > m_socket;
         Deque< Packet > m_recv;
         char * m_recv_msg;
         bool  m_connected;

         void handle_connect(const boost::system::error_code & ec);
         void handle_send(const boost::system::error_code & ec);
         void handle_recv(const boost::system::error_code & ec);

         void handle_recv_header(const boost::system::error_code & ec);
         void handle_recv_packet(const boost::system::error_code & ec);

      public:
         Connection(boost::shared_ptr< boost::asio::io_service> io_serv,
               std::string ip = "localhost",
               std::string port = "13371" );
         ~Connection();

         void recv();
         void send(std::string msg);
   };
} //sdl_platformer
#endif //_CONNECTION_
