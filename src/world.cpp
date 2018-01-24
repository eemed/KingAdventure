#include "world.h"
using namespace utils;
namespace games
{
    World::World(SDL_Renderer * renderer, TTF_Font * fnt, Player player)
        : renderer(renderer), fnt(fnt), posX(0), posY(0), player(player)
    {
        //Testing
        //renderables.push_back( Renderable(0,0,100,50,"FOO"));
        //renderables.push_back( Renderable(0,800,1600,50,"FOO"));
        int xp = 0;
        int yp = 100;
        int b = 40;
        renderables.push_back( Renderable(0 * b + xp, 0 * b + yp,37 * b, 1 * b,"FOO"));
        renderables.push_back( Renderable(0 * b + xp, 1 * b + yp,1 * b, 8 * b,"FOO"));
        renderables.push_back( Renderable(36 * b + xp, 1 * b + yp,1 * b, 8 * b,"FOO"));
        renderables.push_back( Renderable(1 * b + xp, 8 * b + yp,35 * b, 1 * b,"FOO"));
        renderables.push_back( Renderable(2 * b + xp, 6 * b + yp,1 * b, 1 * b,"FOO"));
        renderables.push_back( Renderable(2 * b + xp, 7 * b + yp,15 * b, 2 * b,"FOO"));
        renderables.push_back( Renderable(6 * b + xp, 5 * b + yp,4 * b, 2 * b,"FOO"));
        renderables.push_back( Renderable(11 * b + xp, 2 * b + yp,2 * b, 2 * b,"FOO"));

        renderables.push_back( Renderable(14 * b + xp, 5 * b + yp,1 * b, 2 * b,"FOO"));
        renderables.push_back( Renderable(15 * b + xp, 4 * b + yp,2 * b, 3 * b,"FOO"));
        renderables.push_back( Renderable(17 * b + xp, 3 * b + yp,2 * b, 4 * b,"FOO"));
        renderables.push_back( Renderable(28 * b + xp, 5 * b + yp,3 * b, 2 * b,"FOO"));
        renderables.push_back( Renderable(30 * b + xp, 3 * b + yp,3 * b, 4 * b,"FOO"));

        renderables.push_back( Renderable(30 * b + xp, 6 * b + yp,6 * b, 2 * b,"FOO"));
    }

    World::~World()
    {
    }

    void World::runGame()
    {
        const Uint8 * keys = SDL_GetKeyboardState(NULL);

        const double dt = 0.01;
        int prevTime = 0;
        int currentTime = SDL_GetTicks();
        float deltaTime = 0;
        double accumulator = 0;

        bool cont = true;

        while( cont )
        {
            prevTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime = (currentTime - prevTime) / 1000.0f;

            SDL_Event event;
            while( SDL_PollEvent( &event ) )
            {
                if( event.type == SDL_QUIT )
                {
                    cont = false;
                }
                else if( event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_SPACE:
                            player.jump(deltaTime);
                            break;
                        default:
                            break;
                    }
                }
            }

            // Update keys
            SDL_PumpEvents();
            if( keys[SDL_SCANCODE_RIGHT] and keys[SDL_SCANCODE_LSHIFT])
                player.speedRight(deltaTime);
            else if( keys[SDL_SCANCODE_RIGHT] )
                player.moveRight(deltaTime);
            if( keys[SDL_SCANCODE_LEFT] and keys[SDL_SCANCODE_LSHIFT])
                player.speedLeft(deltaTime);
            else if( keys[SDL_SCANCODE_LEFT] )
                player.moveLeft(deltaTime);
            if( keys[SDL_SCANCODE_Q] )
                cont = false;


            accumulator += deltaTime;

            if( accumulator >= dt )
            {
                update( dt );
                accumulator -= dt;
            }

            render();
        }
    }

    void World::update(const double & deltaTime)
    {
        //Loop throuh all renderables and update them
        //
        //
        player.update(renderables, deltaTime);
    }

    void World::render()
    {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );

        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 100 );
        SDL_RenderFillRect( renderer, &(player.getRect() ));
        // Iterate over the renderables
        SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
        for(std::vector< Renderable >::size_type i = 0; i < renderables.size(); ++i)
        {
            SDL_RenderFillRect( renderer, &(renderables[i].getRect() ));
        }
        // Render the changes above
        SDL_RenderPresent( renderer );
    }
}
