/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Apple
*/

#include "Apple.hpp"

Games::Apple::Apple(int x, int y)
{
    Arcade::Color_t color = {0, 0, 0, 0};
    Arcade::Color_t bg = {255, 0, 0, 0};
    Arcade::SpriteRect_t rect = {0, 0, 64, 64, 64, 64};

    this->_apple = {x, y, "./assets/nibbler/apple", rect, color, bg, 1};
}

Games::Apple::~Apple()
{
}

Arcade::Sprites_t Games::Apple::getApple()
{
    return (this->_apple);
}