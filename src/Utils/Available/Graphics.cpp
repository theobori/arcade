/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Graphics available
*/

#include "Graphics.hpp"

Utils::Graphics::Graphics()
:
_available({
    {"ncurses", "lib/arcade_ncurses.so"},
    {"sdl2", "lib/arcade_sdl2.so"},
    {"sfml", "lib/arcade_sfml.so"},
    {"ndk++", "lib/arcade_ndk++.so"},
    {"aa-lib", "lib/arcade_aalib.so"},
    {"libcaca", "lib/arcade_libcaca.so"},
    {"allegro5", "lib/arcade_allegro5.so"},
    {"xlib", "lib/arcade_xlib.so"},
    {"gtk+", "lib/arcade_gtk+.so"},
    {"irrlicht", "lib/arcade_irrlicht.so"},
    {"opengl", "lib/arcade_opengl.so"},
    {"vulkan", "lib/arcade_vulkan.so"},
    {"qt5", "lib/arcade_qt5.so"}
})
{
    this->_ret = {};
}

Utils::Graphics::~Graphics()
{
}

void Utils::Graphics::fill()
{
    for (const auto it : this->_available) {
        std::ifstream f(it.second, std::ios::in);

        if (f.is_open() == false)
            continue;

        this->_ret.push_back({ it.first, it.second});
    }
    // if (this->_ret.size() < 1)
    //     std::cerr << "Missing Graphics library" << std::endl;
}

std::vector<std::pair<std::string, std::string>> Utils::Graphics::getData() const
{
    return (this->_ret);
}

std::size_t Utils::Graphics::getCount() const
{
    return (this->_ret.size());
}
