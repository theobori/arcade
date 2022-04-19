/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Games available
*/

#include "Games.hpp"

Utils::Games::Games()
:
_available({
    {"menu", "lib/arcade_menu.so"},
    {"nibbler", "lib/arcade_nibbler.so"},
    {"pacman", "lib/arcade_pacman.so"},
    {"qix", "lib/arcade_qix.so"},
    {"centipede", "lib/arcade_centipede.so"},
    {"solarfox", "lib/arcade_solarfox.so"}
})
{
    this->_ret = {};
}

Utils::Games::~Games()
{
}

void Utils::Games::fill()
{
    for (const auto it : this->_available) {
        std::ifstream f(it.second, std::ios::in);

        if (f.is_open() == false)
            continue;

        this->_ret.push_back({ it.first, it.second});
    }
    // if (this->_ret.size() < 1)
    //     std::cerr << "Missing Games" << std::endl;
    // if (this->_ret.at(0).first != "menu")
    //     std::cerr << "Missing the menu" << std::endl;
}

std::vector<std::pair<std::string, std::string>> Utils::Games::getData() const
{
    return (this->_ret);
}

std::size_t Utils::Games::getCount() const
{
    return (this->_ret.size());
}
