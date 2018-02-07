#include <fstream>
#include <list>
#include <boost/filesystem.hpp>

#include "generator.h"
#include "json.hpp"

using json = nlohmann::json;

namespace sdl_platformer
{
   std::string generate_world(unsigned int seed, int width)
   {
      std::vector< Rectangle > hitboxes;
      std::vector< Rectangle > decor_back;
      std::vector< Rectangle > decor_top;

      //set seed
      srand(seed);

      std::string name("world_");
      name += std::to_string(seed);
      name += ".json";

      //Starting variables
      int current_height = 12;
      int current_width = 0;
      int block_length = 1;
      int block_size = 64;
      int iterations = width / block_length;

      for(int i = 0; i < iterations; ++i)
      {
         int random = rand() % 2;
         switch( random )
         {
            case 0:
               if( current_height > 0 )
               {
                  current_height -= rand() % 3 * block_size;
               }
               break;

            case 1:
               if( current_height < 50 )
               {
                  current_height += rand() % 3 * block_size;
               }
               break;

            default:
               break;
         }
         hitboxes.push_back( Rectangle(current_width,
                                      current_height,
                                      block_length * block_size,
                                      block_size,
                                      Color(200,200,200,255) ) );
         current_width += block_length * block_size;
      }
      write_to_file( name,
                     hitboxes//,
                     //decor_back,
                     //decor_top
                     );
      return name;
   }
   bool write_to_file( std::string name,
                       std::vector< Rectangle > hitboxes//,
                       //std::vector< Rectangle > decor_back,
                       //std::vector< Rectangle > decor_top
                       )
   {
      json world;
      std::list<json> boxes;
      for( auto & elem : hitboxes )
      {
         json json_element;
         json_element["x"] = elem.get_x();
         json_element["y"] = elem.get_y();
         json_element["w"] = elem.get_width();
         json_element["h"] = elem.get_height();
         boxes.push_back( json_element );
      }
      world["squares"] = boxes;
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "/build/apps/res/worlds/";
      std::ofstream out( ( p.string() + name).c_str() );
      out << std::setw(3) << world << std::endl;
      return true;
   }
}
