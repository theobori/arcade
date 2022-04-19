/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Map
*/

#include "Maps.hpp"

Games::Maps::Maps()
{
    this->_maps = this->my_get_file("./assets/nibbler/map.txt");
    this->loadMaps();
}

Games::Maps::~Maps()
{
}

std::string Games::Maps::my_get_file(std::string filename)
{
    std::string content_file;
    std::stringstream sstr;
    std::ifstream f(filename, std::ios::in);

    sstr << f.rdbuf();
    content_file = sstr.str();
    f.close();
    return (content_file);
}

void Games::Maps::loadMaps()
{
    std::string map = this->_maps;
    int y = 0;
    int addx = 0;
    int addy = 0;

    for (int x = 0; x < map.length(); x++) {
        if (map[x] == '\n') {
            x++;
            y++;
        }
        if (map[x] == 'X')
            this->_mapShape[std::to_string(((y*100) + x))] = {(x % 19) * 64 + addx, y * 64 + addy, 64, 64, {255, 0, 0, 255}, 1};
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::Maps::getMaps()
{
    return (this->_mapShape);
}