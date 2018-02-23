#include "connection.h"

namespace sdl_platformer
{
   Connection::Connection(
         boost::shared_ptr< boost::asio::io_service > io_service,
         std::string ip,
         std::string port)
      :  m_io_service( io_service ),
         m_socket( new boost::asio::ip::tcp::socket( *m_io_service ))
   {
      try
      {
         boost::asio::ip::tcp::resolver resolver( *m_io_service );
         boost::asio::ip::tcp::resolver::query query( ip, port );
         boost::asio::ip::tcp::resolver::iterator iterator =
            resolver.resolve( query );
         boost::asio::ip::tcp::endpoint endpoint = *iterator;

         //Connecting to host
         m_socket->async_connect( endpoint,
               boost::bind( &Connection::handle_connect, this ) );
      }
      catch( std::exception & ex )
      {
         pantheios::log_ERROR("Exception: ", ex);
      }
   }

   Connection::~Connection()
   {
      boost::system::error_code ec;
      m_socket->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
      m_socket->close( ec );
   }

   void
   Connection::handle_connect(const boost::system::error_code & ec)
   {
      if( ec )
      {
         pantheios::log_ERROR("[",  boost::this_thread::get_id(),
               "] Error: ", ec);
      }
      else
      {
         pantheios::log_DEBUG("[", boost::this_thread::get_id(),
               "] Connected to ", m_connected_to);
      }
   }

   void
   Connection::recv(const boost::system::error_code & ec)
   {
      std::string header;
      m_socket.async_receive(
            boost::asio::buffer(header, Packet::HEADER_LEN),
            boost::bind( &Connection::handle_recv_header,
               this, _1, header) );
   }
}
