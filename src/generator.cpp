#include <fstream>
#include <iostream>
#include <list>
#include <boost/filesystem.hpp>

#include "generator.h"
#include "sprite_factory.h"
#include "json.hpp"

using json = nlohmann::json;

namespace sdl_platformer
{
   std::string
   generate_world(unsigned int seed, int width)
   {
      std::vector< Hitbox > hitboxes;
      std::vector< Decor > decor_back;
      //set seed
      srand(seed);

      std::string name("world_");
      name += std::to_string(seed);
      name += ".json";

      //Starting variables
      int current_y = 12;
      int current_x = 0;
      int block_length = 2;
      int block_size = 64;
      int iterations = width / block_length;

      //Before beginning sea
      for(int i = -10; i < 1; ++i)
      {
         Decor new_decor;
         new_decor.x = i * block_size;
         new_decor.y = (current_y + 3) * block_size;
         new_decor.w = block_size;
         new_decor.h = block_size;
         new_decor.sprite = std::string("water_top");
         decor_back.push_back( new_decor );

         for( int j = 1; j < 20; ++j)
         {
            Decor new_ground;
            new_ground.x = i * block_size;
            new_ground.y = (current_y + 3)  * block_size + j * block_size;
            new_ground.w = block_size;
            new_ground.h = block_size;
            int rock = rand() % 20;
            if( rock == 2 )
            {
               new_ground.sprite = std::string("water_deep");
            }
            else
            {
               new_ground.sprite = std::string("ground_in");
            }
            decor_back.push_back( new_ground );

         }
      }

      //Mainland generation
      for(int i = 0; i < iterations; ++i)
      {
         int random = rand() % 2;
         switch( random )
         {
            case 0:
               if( current_y > 0 )
               {
                  current_y -= rand() % 2;
               }
               break;

            case 1:
               if( current_y < 50 )
               {
                  current_y += rand() % 3;
               }
               break;

            default:
               break;
         }

         if( i % 10 == 0)
         {
            Decor new_decor;
            new_decor.x = current_x + (rand() % 2) * block_size;
            new_decor.y = current_y * block_size - 13 * block_size;
            new_decor.w = 8 * block_size;
            new_decor.h = 16 * block_size;
            new_decor.sprite = std::string("tree");
            decor_back.push_back( new_decor );
         }

         Hitbox new_hitbox;
         new_hitbox.x = current_x;
         new_hitbox.y = current_y * block_size;
         new_hitbox.w = block_length * block_size;
         new_hitbox.h = block_size;
         hitboxes.push_back( new_hitbox );

         for(int j = 0; j < block_length; ++j)
         {
            Decor new_decor;
            new_decor.x = current_x + j * block_size;
            new_decor.y = current_y * block_size;
            new_decor.w = block_size;
            new_decor.h = block_size;
            new_decor.sprite = std::string("ground_grass");
            decor_back.push_back( new_decor );

            for( int k = 1; k < 20; ++k)
            {
               Decor new_ground;
               new_ground.x = current_x + j * block_size;
               new_ground.y = current_y * block_size + k * block_size;
               new_ground.w = block_size;
               new_ground.h = block_size;
               int rock = rand() % 20;
               if( rock == 2 )
               {
                  new_ground.sprite = std::string("ground_in_rock");
               }
               else
               {
                  new_ground.sprite = std::string("ground_in");
               }
               decor_back.push_back( new_ground );

            }
         }

         for( int j = 1; j < 20; ++j)
         {
            Hitbox new_hitbox;
            new_hitbox.x = current_x;
            new_hitbox.y = current_y * block_size + j * block_size;
            new_hitbox.w = block_length * block_size;
            new_hitbox.h = block_size;
            hitboxes.push_back( new_hitbox );
         }
         current_x += block_length * block_size;
      }

      //after beginning sea
      for(int i = iterations * block_length; i < iterations * block_length + 10; ++i)
      {
         Decor new_decor;
         new_decor.x = i * block_size;
         new_decor.y = (current_y + 3) * block_size;
         new_decor.w = block_size;
         new_decor.h = block_size;
         new_decor.sprite = std::string("water_top");
         decor_back.push_back( new_decor );

         for( int j = 1; j < 20; ++j)
         {
            Decor new_ground;
            new_ground.x = i * block_size;
            new_ground.y = (current_y + 3)  * block_size + j * block_size;
            new_ground.w = block_size;
            new_ground.h = block_size;
            int rock = rand() % 20;
            if( rock == 2 )
            {
               new_ground.sprite = std::string("water_deep");
            }
            else
            {
               new_ground.sprite = std::string("ground_in");
            }
            decor_back.push_back( new_ground );

         }
      }
      write_to_file( name,
                     hitboxes,
                     decor_back//,
                     //decor_top
                     );
      return name;
   }

   bool
   write_to_file( std::string name,
                       std::vector< Hitbox > hitboxes,
                       std::vector< Decor > decor_back//,
                       //std::vector< Rectangle > decor_top
                       )
   {
      json world;
      std::list<json> boxes;
      std::list<json> l_decor;
      for( auto & elem : hitboxes )
      {
         json json_element;
         json_element["x"] = elem.x;
         json_element["y"] = elem.y;
         json_element["w"] = elem.w;
         json_element["h"] = elem.h;
         boxes.push_back( json_element );
      }
      for( auto & elem : decor_back )
      {
         json json_element;
         json_element["x"] = elem.x;
         json_element["y"] = elem.y;
         json_element["w"] = elem.w;
         json_element["h"] = elem.h;
         json_element["texture"] = elem.sprite;
         l_decor.push_back( json_element );
      }
      world["squares"] = boxes;
      world["decor_back"] = l_decor;
      boost::filesystem::path p = boost::filesystem::current_path();
      p /= "/build/apps/res/worlds/";
      std::ofstream out( ( p.string() + name).c_str() );
      out << std::setw(3) << world << std::endl;
      return true;
   }
}
