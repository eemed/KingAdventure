#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <ctime>
#include "shape.h"
#include "board.h"
#include "menu.h"
//#include "res_path.h"

bool initAll();
bool initSDL();
bool createWindow();
bool createRenderer();
void setupRenderer();


bool setupTTF( const std::string &fontName );
SDL_Texture* surfaceToTexture( SDL_Surface* surf );
void createTextTextures();

void render();
void runGame();

void changeColor();

//windowpos
int posX = 600;
int posY = 100;
int sizeX = 600;
int sizeY = 850;
int blockSize = 40;
std::string fontPath = "/usr/share/fonts/truetype/roboto/hinted/Roboto-Bold.ttf";
// take away the 10 block sizes and the gaps +1 from screen width
int sidebar = (sizeX - 10 * (blockSize + 1)) / 2;

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

int r[3] = { 255, 0, 0 };
int g[3] = { 0, 255, 0 };
int y[3] = { 255, 255, 0 };
int o[3] = { 255, 128, 0 };
int p[3] = { 255, 0, 255 };
int v[3] = { 128, 0, 255 };
//Functions for setting colors
void setRandomColor();
void setColor();

SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8 *wavBuffer;
SDL_AudioDeviceID deviceId;

int main()
{
    if( !initAll() )
    {
        return -1;
    }
    SDL_LoadWAV("/home/eeme/code/cpp/tetris/build/apps/res/tetris.wav", &wavSpec, &wavBuffer, &wavLength);

    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    block.w = blockSize;
    block.h = blockSize;

    setRandomColor();

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
                            setRandomColor();
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
                setRandomColor();
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

bool initAll()
{
    if ( !initSDL() )
        return false;

    if ( !createWindow() )
        return false;

    if ( !createRenderer() )
        return false;

    setupRenderer();

    if ( !setupTTF(fontPath.c_str()) )
        return false;

    return true;
}

bool initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool createWindow()
{
    window = SDL_CreateWindow("Tetris", posX, posY, sizeX, sizeY, 0);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

void setupRenderer()
{
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, sizeX, sizeY );
    // Set color of renderer to red
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
}

void setColor(int * a)
{
    red = a[0];
    green = a[1];
    blue = a[2];
}
void setRandomColor()
{
    std::srand(std::time(nullptr));
    int a = std::rand() % 6;
    switch( a )
    {
        case 0:
            setColor( r );
            break;
        case 1:
            setColor( g );
            break;
        case 2:
            setColor( o );
            break;
        case 3:
            setColor( p );
            break;
        case 4:
            setColor( v );
            break;
        case 5:
            setColor( y );
            break;
        default:
            break;
    }
}

bool setupTTF( const std::string &fontName )
{
    if( TTF_Init() == -1 )
    {
        std::cout << " Failed to init TTF: " << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont( fontName.c_str(), 24);

    if ( font == nullptr )
    {
        std::cout << " Failed to laod font: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Texture* surfaceToTexture( SDL_Surface* surf )
{
    SDL_Texture * text;
    text = SDL_CreateTextureFromSurface( renderer, surf );
    SDL_FreeSurface( surf );
    return text;
}
