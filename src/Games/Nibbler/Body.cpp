/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** body
*/

#include "Body.hpp"

Games::Body::Body(int x, int y, int num)
{
    Arcade::Color_t text = {0, 0, 0, 0};
    Arcade::Color_t bg = {255, 0, 0, 0};
    Arcade::SpriteRect_t rect = {0, 0, 32, 32, 32, 32};
    this->_body = {x, y, "./assets/nibbler/body", rect, text, bg, 1};
    this->_num = num;
}

Games::Body::~Body()
{
}

void Games::Body::SetPos(int x, int y)
{
    this->_body.x = x;
    this->_body.y = y;
}

Arcade::Sprites_t Games::Body::getBody()
{
    return (this->_body);
}

void Games::Body::walk(std::pair<int, int> pos)
{
    int speed = 4;

    if (this->_body.x < pos.first)
        this->_body.x += speed;
    if (this->_body.x > pos.first)
        this->_body.x -= speed;
    if (this->_body.y < pos.second)
        this->_body.y += speed;
    if (this->_body.y > pos.second)
        this->_body.y -= speed;
}

int Games::Body::getX()
{
    return (this->_body.x);
}
int Games::Body::getY()
{
    return (this->_body.y);
}