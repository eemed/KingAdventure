#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "utils.h"
#include "tetris.h"
#include "world.h"
using namespace utils;
using namespace games;

void launch(int selected);

//Window settings
int posX = 160;
int posY = 90;
int sizeX = 1600;
int sizeY = 900;

//Font path
std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

// take away the 10 block sizes and the gaps +1 from screen width
int xPadding = (sizeX - 10 * (40 + 1)) / 2;

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;

//Colors
SDL_Color textColor = { 255, 255, 255, 255 }; // white
SDL_Color backgroundColor = { 0, 0, 0, 255 }; // black

SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;
SDL_AudioDeviceID deviceId;

//SDL_LoadWAV("/home/eeme/code/cpp/tetris/build/apps/res/tetris.wav", &wavSpec, &wavBuffer, &wavLength);

//deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
int main()
{
    //Load SDL
    initSDL();
    //Create window and renderer
    window = createWindow(posX, posY, sizeX, sizeY);
    renderer = createRenderer(window);
    setupRenderer(renderer, sizeX, sizeY);
    //Load font
    font = setupTTF( fontPath );



    sdl_games::Menu menu( font, renderer);
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
            else if( event.type == SDL_KEYDOWN )
            {
                // Handle keypresses
                switch ( event.key.keysym.sym )
                {
                    case SDLK_q:
                        cont = false;
                        break;
                    case SDLK_SPACE:
                        launch( menu.getSelected() );
                        break;
                    case SDLK_DOWN:
                        menu.down();
                        break;
                    case SDLK_UP:
                        menu.up();
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                    default:
                        break;
                }
            }
        }
        menu.render();
        // ~140 FPS
        SDL_Delay( 8 );
    }
}

void launch(int selected)
{
    games::Tetris  *t = NULL;
    games::World * w = NULL;
    std::cout << selected << std::endl;
    switch( selected )
    {
        case 0:
            t = new(games::Tetris)(renderer, font, 200);
            t->runGame();
            delete t;
            break;
        case 1:
            w = new(games::World)(renderer, font, games::Player ("Jonne"));
            w->runGame();
            delete w;
            break;

        default:
            break;
    }
}
