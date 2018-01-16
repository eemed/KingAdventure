#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace sdl_games
{
    class Menu
    {
        private:
            unsigned int selected; // Index of currently selected
            std::vector< std::string > games; // Vector of all the options
            unsigned int size_m;
            TTF_Font * fnt;
            SDL_Color textColor;
            SDL_Color backgroundColor;
            SDL_Color selectedColor;
            std::vector< std::pair<SDL_Texture *, SDL_Rect> > textures;
            int x;
            int y;
            SDL_Renderer * renderer;
        public:
            Menu(TTF_Font *, SDL_Renderer *);
            Menu(TTF_Font * fnt, SDL_Renderer * renderer, std::vector< std::string > t);

            ~Menu();
            void up();
            void down();
            void press() const;
            bool add(std::string); // add to end
            bool add(std::string, unsigned int i); // add to index i

            bool del(std::string); // Delete this menu entry
            bool del(unsigned int i); //delete entry in this index
            bool del(); // Delete currently selected

            unsigned int getSelected() const;
            unsigned int size() const;
            bool updateTextures();
            void render() const;

            friend std::ostream & operator<<(std::ostream & out, const Menu & menu);
    };
    std::ostream & operator<<(std::ostream & out, const Menu & menu);
}
