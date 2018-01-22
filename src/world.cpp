#include "world.h"
using namespace utils;
namespace games
{
    World::World(SDL_Renderer * renderer, TTF_Font * fnt, Player player)
        : renderer(renderer), fnt(fnt), posX(0), posY(0), player(player)
    {
        //Testing
        renderables.push_back( Renderable(0,0,100,50,"FOO"));
        renderables.push_back( Renderable(0,800,1600,50,"FOO"));
    }

    World::~World()
    {
    }

    void World::runGame()
    {
        const Uint8 * keys = SDL_GetKeyboardState(NULL);
        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;
        bool cont = true;

        while( cont )
        {
            SDL_Event event;
            while( SDL_PollEvent( &event ) )
            {
                if( event.type == SDL_QUIT )
                {
                    cont = false;
                }
            }

            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = ((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
            // Update keys
            SDL_PumpEvents();
            if( keys[SDL_SCANCODE_RIGHT] )
                player.moveRight(deltaTime);
            if( keys[SDL_SCANCODE_LEFT] )
                player.moveLeft(deltaTime);
            if( keys[SDL_SCANCODE_Q] )
                cont = false;

            SDL_Delay( 8 );
            player.update(renderables, 3, deltaTime);
            render();
        }
    }

    void World::render()
    {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );

        SDL_RenderFillRect( renderer, &(player.getRect() ));
        // Iterate over the renderables
        for(std::vector< Renderable >::size_type i = 0; i < renderables.size(); ++i)
        {
            SDL_RenderFillRect( renderer, &(renderables[i].getRect() ));
        }
        // Render the changes above
        SDL_RenderPresent( renderer );
    }
}
