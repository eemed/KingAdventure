#include "utils.h"
namespace utils
{
    int r[3] = { 255, 0, 0 };
    int g[3] = { 0, 255, 0 };
    int y[3] = { 255, 255, 0 };
    int o[3] = { 255, 128, 0 };
    int p[3] = { 255, 0, 255 };
    int v[3] = { 128, 0, 255 };
    int w[3] = { 255, 255, 255 };


    // Basic SDL functions
    // initilizing sdl window and renderer
    bool initSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    SDL_Window * createWindow(const int & posX, const int & posY,
            const int & sizeX, const int & sizeY)
    {
        SDL_Window * window = SDL_CreateWindow("Tetris", posX, posY, sizeX, sizeY, 0);
        if (window == nullptr){
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return window;
    }

    SDL_Renderer * createRenderer(SDL_Window * window)
    {
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr){
            SDL_DestroyWindow(window);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return renderer;
    }

    void setupRenderer(SDL_Renderer * renderer, const int & sizeX, const int & sizeY)
    {
        SDL_RenderSetLogicalSize( renderer, sizeX, sizeY );
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    }

    void setColor(int * a, int & red, int & green, int & blue)
    {
        red = a[0];
        green = a[1];
        blue = a[2];
    }
    void setRandomColor(int & red, int & green, int & blue)
    {
        std::srand(std::time(nullptr));
        int a = std::rand() % 6;
        switch( a )
        {
            case 0:
                setColor( r, red, green, blue );
                break;
            case 1:
                setColor( g, red, green, blue );
                break;
            case 2:
                setColor( o, red, green, blue );
                break;
            case 3:
                setColor( p, red, green, blue );
                break;
            case 4:
                setColor( v, red, green, blue );
                break;
            case 5:
                setColor( y, red, green, blue );
                break;
            case 6:
                setColor( w, red, green, blue );
                break;
            default:
                break;
        }
    }

    // Setup font and return it
    TTF_Font * setupTTF( const std::string &fontName )
    {
        if( TTF_Init() == -1 )
        {
            std::cout << " Failed to init TTF: " << SDL_GetError() << std::endl;
            return NULL;
        }

        TTF_Font * font = TTF_OpenFont( fontName.c_str(), 24);

        if ( font == nullptr )
        {
            std::cout << " Failed to laod font: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return font;
    }

    //From surface to texture
    SDL_Texture * surfaceToTexture( SDL_Surface* surf , SDL_Renderer * renderer)
    {
        SDL_Texture * text;
        text = SDL_CreateTextureFromSurface( renderer, surf );
        SDL_FreeSurface( surf );
        return text;
    }

    //Renderable class
    Renderable::Renderable(int x, int y, int width, int height, std::string spritePath)
        : spritePath( spritePath )
    {
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    Renderable::~Renderable()
    {
    }

    bool Renderable::isOverlapping(const SDL_Rect & r) const
    {
        if( ( ( rect.x + rect.w <= r.x) or ( rect.x >= r.x + r.w ) ) or
             ( ( rect.y + rect.h <= r.y) or ( rect.y >= r.y + r.h ) ) )
        {
            return false;
        }
        return true;
    }

    SDL_Rect & Renderable::getRect()
    {
        return rect;
    }
    SDL_Rect Renderable::getRect() const
    {
        return rect;
    }

    int Renderable::getYHigh()
    {
        return rect.y;
    }
    int Renderable::getXHigh()
    {
        return rect.x + rect.w;
    }
    int Renderable::getYLow()
    {
        return rect.y + rect.h;
    }
    int Renderable::getXLow()
    {
        return rect.x;
    }
    int Renderable::getMiddleX()
    {
        return rect.x + ( rect.w / 2 );
    }
    int Renderable::getMiddleY()
    {
        return rect.y + ( rect.h / 2 );
    }
    int Renderable::getHalfXLen()
    {
        return getMiddleX() - rect.x;
    }

    int Renderable::getHalfYLen()
    {
        return getMiddleY() - rect.y;
    }

    CollisionVector::CollisionVector(int x, int y)
        : x(x), y(y)
    {
    }
}
