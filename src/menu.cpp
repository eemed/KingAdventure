#include "menu.h"
namespace my_tetris
{
    Menu::Menu()
        : selected(0), size_m(0)
    {
    }

    Menu::Menu(std::vector< std::string > entries)
        : selected(0), options(entries), size_m(entries.size())
    {
    }

    Menu::~Menu()
    {
    }

    void Menu::up()
    {
        if( selected + 1 < size_m )
        {
            selected += 1;
        }
    }

    void Menu::down()
    {
        if( selected != 0 )
        {
            selected -= 1;
        }
    }

    bool Menu::add(const std::string s) // add to end
    {
        options.push_back( s );
        size_m += 1;
        return true;
    }

    bool Menu::add(const std::string s, unsigned int i) // add to index i
    {
        if( i >= size_m )
        {
            return false;
        }
        else
        {
            options.push_back( s );
            size_m += 1;
            return true;
        }
    }

    bool Menu::del(std::string s) // Delete this menu entry
    {
        for(std::vector< std::string >::size_type i = 0; i < options.size(); ++i)
        {
            if( s == options[i] )
            {
                options.erase( options.begin() + i );
                return true;
            }
        }
        return false;
    }

    bool Menu::del(unsigned int i) //delete entry in this index
    {
        if( i >= size_m )
        {
            return false;
        }
        else
        {
            options.erase( options.begin() + selected );
            return true;
        }
    }

    bool Menu::del() // Delete currently selected
    {
        options.erase( options.begin() + selected);
        return true;
    }

    unsigned int Menu::getSelected() const
    {
        return selected;
    }

    unsigned int Menu::size() const
    {
        return size_m;
    }

    std::ostream & operator<<(std::ostream & out, const Menu & menu)
    {
        for(unsigned int i = 0; i < menu.size_m; ++i)
        {
            out << i+1 << ": " << menu.options[i] << std::endl;
        }
        return out;
    }
}
