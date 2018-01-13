#include <vector>
#include <string>
#include <iostream>
namespace my_tetris
{
    class Menu
    {
        private:
            unsigned int selected; // Index of currently selected
            std::vector< std::string > options; // Vector of all the options
            unsigned int size_m;
        public:
            Menu();
            Menu(std::vector< std::string > t);

            ~Menu();
            void up();
            void down();
            bool add(std::string); // add to end
            bool add(std::string, unsigned int i); // add to index i

            bool del(std::string); // Delete this menu entry
            bool del(unsigned int i); //delete entry in this index
            bool del(); // Delete currently selected

            unsigned int getSelected() const;
            unsigned int size() const;

            friend std::ostream & operator<<(std::ostream & out, const Menu & menu);
    };
    std::ostream & operator<<(std::ostream & out, const Menu & menu);
}
