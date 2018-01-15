#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "utils.h"
#include "tetris.h"
using namespace utils;
using namespace games;

//Window settings
int posX = 600;
int posY = 100;
int sizeX = 600;
int sizeY = 850;

//Font path
std::string fontPath = "/usr/share/fonts/truetype/roboto/hinted/Roboto-Bold.ttf";

// take away the 10 block sizes and the gaps +1 from screen width
int xPadding = (sizeX - 10 * (40 + 1)) / 2;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect block;
TTF_Font* font;

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

    //SDL_LoadWAV("/home/eeme/code/cpp/tetris/build/apps/res/tetris.wav", &wavSpec, &wavBuffer, &wavLength);

    //deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    Tetris t(renderer, font, xPadding);
    t.runGame();
}
