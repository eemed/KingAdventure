#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <ctime>
#include "shape.h"
#include "board.h"
#include "menu.h"
#include "utils.h"
using namespace utils;
//#include "res_path.h"

void render();
void runGame();

void changeColor();

//Window settings
int posX = 600;
int posY = 100;
int sizeX = 600;
int sizeY = 850;
int blockSize = 40;

//Font path
std::string fontPath = "/usr/share/fonts/truetype/roboto/hinted/Roboto-Bold.ttf";

// take away the 10 block sizes and the gaps +1 from screen width
int sidebar = (sizeX - 10 * (blockSize + 1)) / 2;

//Colors to use while rendering
int red;
int green;
int blue;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect block;
TTF_Font* font;

//Init board
my_tetris::TetrisBoard board(10, 22);

//Colors
SDL_Color textColor = { 255, 255, 255, 255 }; // white
SDL_Color backgroundColor = { 0, 0, 0, 255 }; // black

SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;
SDL_AudioDeviceID deviceId;

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

    SDL_LoadWAV("/home/eeme/code/cpp/tetris/build/apps/res/tetris.wav", &wavSpec, &wavBuffer, &wavLength);

    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    block.w = blockSize;
    block.h = blockSize;

    setRandomColor(red, green, blue);

    board.mergeShape(my_tetris::getRandom(), 2,5);

    runGame();
}

void runGame()
{
    bool cont = true;
    unsigned int time = 0;
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
                switch ( event.key.keysym.sym )
                {
                    case SDLK_q:
                        cont = false;
                        break;

                    case SDLK_SPACE:
                        //std::cout << "x: " << board.getPivot().first << ", y: "
                        //    << board.getPivot().second << std::endl;
                        board.rotateShape();
                        break;
                    case SDLK_DOWN:
                        //if board cannot be pushed down
                        //everythin is stuck so create new shape
                        if( !board.pushDown() )
                        {
                            setRandomColor(red, green, blue);
                            board.mergeShape(my_tetris::getRandom(), 2,5);
                        }
                        if( board.checkRow() )
                        {
                            SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                            SDL_PauseAudioDevice( deviceId, 0);
                        }
                        break;
                    case SDLK_LEFT:
                        board.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        board.moveRight();
                        break;

                    /*
                    case SDLK_f:
                        board.checkRow();
                        break;
                    */
                    default:
                        break;
                }
            }
        }
        if( time >= 30 )
        {
            if( !board.pushDown() )
            {
                setRandomColor(red, green, blue);
                board.mergeShape(my_tetris::getRandom(), 2,5);
            }

            if( board.checkRow() )
            {
                SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                SDL_PauseAudioDevice( deviceId, 0);
            }

            if( board.lost() )
            {
                cont = false;
            }
            time = 0;
        }

        SDL_Delay( 8 );

        render();
        ++time;
    }
}

void render()
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );

    for(std::vector< std::vector<my_tetris::Square> >::size_type i = 2; i < board.board.size(); ++i)
    {
        for(std::vector<my_tetris::Square>::size_type j = 0; j < board.board[i].size(); ++j)
        {
            block.x = blockSize * j + j + sidebar;
            block.y = blockSize * (i-2) + (i-2);
            if( board.board[i][j].getType() == my_tetris::ACTIVE )
            {
                if( board.board[i][j].getStuck() == true )
                {
                    SDL_SetRenderDrawColor( renderer, 50, 50, 255, 255 );
                    SDL_RenderFillRect(renderer, &block);
                }
                else
                {
                    SDL_SetRenderDrawColor( renderer, red,
                            green, blue, 255 );
                    SDL_RenderFillRect(renderer, &block);
                }
            }
            else if( board.board[i][j].getType() == my_tetris::PIVOT )
            {
                SDL_SetRenderDrawColor( renderer, red, green, blue, 255 );
                SDL_RenderFillRect(renderer, &block);
            }
            else if( board.board[i][j].getType() == my_tetris::DISABLED )
            {
                SDL_SetRenderDrawColor( renderer, 20, 20, 20, 255 );
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
    // Render the changes above
    SDL_RenderPresent( renderer );
}
