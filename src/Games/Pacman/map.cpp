/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** map
*/

#include "Pacman.hpp"

void Games::Pacman::loadMaps()
{
    std::string map = this->_maps;
    int y = 0;
    int addx = 32 * 10;
    int addy = 32 * 4;
    Arcade::Color_t bg = {0, 0, 0, 0};
    Arcade::Color_t text = {255, 255, 255, 0};
    Arcade::Color_t textBoost = {0, 255, 255, 0};
    Arcade::SpriteRect_t rect = {0, 0, 32, 32, 32, 32};

    for (int x = 0; x < map.length(); x++) {
        if (map[x] == '\n') {
            x++;
            y++;
        }
        if (map[x] == 'X')
            this->_mapShape.push_back({(x % 22) * 32 + addx, y * 32 + addy, 32, 32, {0, 0, 255, 255}, 0});
        if (map[x] == '.')
            this->_dostShape.push_back({(x % 22) * 32 + addx, y * 32 + addy, "./assets/pacman/dot", rect, text, bg, 0});
        if (map[x] == 'F')
            this->_dostShape.push_back({(x % 22) * 32 + addx, y * 32 + addy, "./assets/pacman/bigDot", rect, textBoost, bg, 0});
        if (map[x] == 'D')
            this->_door = {(x % 22) * 32 + addx, y * 32 + addy, 32, 32, {128, 128, 128, 255}, 0};
    }
    this->_mapIsLoad = true;
}

void Games::Pacman::displayMaps()
{
    if (!this->_mapIsLoad) {
        this->loadMaps();
        return;
    }
    int t = 0;
    for (const auto it: this->_mapShape) {
        this->_shapes["maps" + std::to_string(t)] = it;
        t++;
    }
    t = 0;
    for (const auto it: this->_dostShape) {
        this->_sprites["point" + std::to_string(t) + it.path] = it;
        t++;
    }
    if (!this->_startGhost)
        this->_shapes["door"] = this->_door;
}

void Games::Pacman::checkDots()
{
    std::pair<int, int> pos = this->_pacman->getPos();

    for ( size_t t = 0; t < this->_dostShape.size(); ++t) {
    // for (const auto it: this->_dostShape) {
        if (this->_dostShape[t].x == pos.first && this->_dostShape[t].y == pos.second && this->_dostShape.at(t).path == "./assets/pacman/dot") {
            this->_dostShape.erase(this->_dostShape.begin()+t);
            this->_score += 10;
            continue;
        }
        if (this->_dostShape[t].x == pos.first && this->_dostShape[t].y == pos.second  && this->_dostShape.at(t).path == "./assets/pacman/bigDot") {
            this->_ghostInactif = true;
            this->_blueGhost->startInactifClock();
            this->_redGhost->startInactifClock();
            this->_pinkGhost->startInactifClock();
            this->_orangeGhost->startInactifClock();
            this->_ghostInactifClock->reset();
            this->_dostShape.erase(this->_dostShape.begin()+t);
        }
    }
    if (this->_ghostInactifClock->check())
        this->_ghostInactif = false;
}