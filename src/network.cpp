#include "network.h"
namespace sdl_platformer
{
   Network::Network() :
      m_io_service(new boost::asio::io_service ),
      m_connected(false),
      m_curr_conn( 0 )
   {
      m_threads.create_thread(
            boost::bind(&Network::create_thread, this, m_io_service) );

      m_threads.create_thread(
            boost::bind(&Network::create_thread, this, m_io_service) );
   }

   Network::~Network()
   {
      if( m_curr_conn != 0 )
      {
         delete m_curr_conn;
      }
      m_io_service->stop();
      m_threads.join_all();
   }

   bool
   Network::connect_to(std::string ip, std::string port)
   {
      if( m_curr_conn != 0 )
      {
         delete m_curr_conn;
      }

      m_curr_conn = new Connection(m_io_service, ip, port);
      std::cout << "Created Connection\n";
      return true;
   }

   bool
   Network::disconnect()
   {
      if( m_curr_conn != 0 )
      {
         delete m_curr_conn;
      }
      return true;
   }

   bool
   Network::send_message(std::string msg)
   {
      if( m_curr_conn != 0)
      {
         m_curr_conn->send(msg);
         std::cout << "Sent\n";
         return true;
      }
      std::cout << "not connected\n";
      return false;
   }

   void
   Network::create_thread( boost::shared_ptr< boost::asio::io_service > m_io_service)
   {
      std::cout << "Thread started\n";
      while( true )
      {
         try
         {
            boost::system::error_code ec;
            m_io_service->run( ec );
            if( ec )
            {
               std::cout << "create thread\n";
            }
            break;
         }
         catch( std::exception & ex )
         {
            std::cout << "create thread EXP\n";
         }
      }
      std::cout << "Thread exited\n";
   }

   /*
   bool
   Network::send_location_data(Player p)
   {
      if( m_curr_conn != 0)
      {
         m_curr_conn->send(msg);
      }
   }
   */
} // sdl_platformer
