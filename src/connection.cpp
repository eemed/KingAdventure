#include "connection.h"

#include <iomanip>
#include <sstream>
//#include "easylogging++.h"

//INITIALIZE_EASYLOGGINGPP

namespace sdl_platformer
{
   Connection::Connection(
         boost::shared_ptr< boost::asio::io_service > io_service,
         std::string ip,
         std::string port)
      :  m_io_service( io_service ),
         m_socket( new boost::asio::ip::tcp::socket( *m_io_service )),
         m_recv_msg( nullptr )

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
               boost::bind( &Connection::handle_connect, this, _1 ) );
      }
      catch( std::exception & ex )
      {
         m_connected = false;
         //LOG(ERROR) << "Exception: " << ex;
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
         m_connected = false;
         std::cout << "Moi\n";
         //LOG(ERROR) << "[" <<  boost::this_thread::get_id() <<
         //      "] Error: " << ec;
      }
      else
      {
         m_connected = true;
         std::cout << "oi\n";
         //LOG(DEBUG) << "[" <<  boost::this_thread::get_id() <<
         //      "] Connected to " << m_connected_to;
      }
   }

   void
   Connection::recv()
   {
      if( m_socket->is_open() )
      {
         m_socket->async_receive(
               boost::asio::buffer(m_recv_msg, Packet::HEADER_LEN),
               boost::bind( &Connection::handle_recv_header,
                  this, _1) );
      }
   }

   void
   Connection::handle_recv_header(const boost::system::error_code & ec)
   {
      if( m_socket->is_open() and !ec )
      {
         size_t size = (size_t) atoi(m_recv_msg);
         m_socket->async_receive(
               boost::asio::buffer(m_recv_msg, size),
               boost::bind( &Connection::handle_recv_packet,
                  this, _1 ) );
      }
   }

   void
   Connection::handle_recv_packet(const boost::system::error_code & ec)
   {
      if( !ec )
      {
         std::cout << "Error handle recv packet\n";
      }
      else
      {
         m_recv_msg = nullptr;
      }
   }

   void
   Connection::send(std::string msg)
   {
      if( m_socket->is_open() )
      {
         std::ostringstream oss;
         oss << std::setfill('0') <<
            std::setw(Packet::HEADER_LEN) << msg.size();

         std::string with_header = oss.str() + msg;
         //Sending
         m_socket->async_send(
               boost::asio::buffer(with_header, with_header.size() ),
               boost::bind( &Connection::handle_send, this, _1) );
         std::cout << "Sock open\n";
      }
      else
      {
         std::cout << "Sock not open\n";
      }
   }

   void
   Connection::handle_send(const boost::system::error_code & ec)
   {
      if( !ec )
      {
         std::cout << "Error handle send\n";
      }
      else
      {
         std::cout << "sent handle\n";
      }
   }
}
