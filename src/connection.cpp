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
      if( m_socket.is_open() and !ec)
      {
         m_socket.async_receive(
               boost::asio::buffer(m_recv_msg, Packet::HEADER_LEN),
               boost::bind( &Connection::handle_recv_header,
                  this ) );
      }
   }

   void
   Connection::handle_recv_header(const boost::system::error_code & ec,
         size_t size)
   {
      if( m_socket.is_open() and !ec )
      {
         size_t size = (size_t) atoi(m_recv+_msg);
         m_socket.async_receive(
               boost::asio::buffer(m_recv_msg, size),
               boost::bind( &Connection::handle_recv_packet,
                  this ) );
      }
   }

   void
   Connection::handle_recv_packet(const boost::system::error_code & ec)
   {
      if( !ec )
      {
         Packet packet;
         packet.parse_from(m_recv_msg);
         m_recv.push_back(packet);
      }
      else
      {
         m_recv_msg = nullptr;
      }
   }
}
