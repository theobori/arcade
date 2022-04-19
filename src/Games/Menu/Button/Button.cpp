/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** button
*/

#include "Button.hpp"

Games::Button::Button(Games::Button::TYPE type, Arcade::Sprites_t sprite)
{
    this->_type = type;
    this->_sprite = sprite;
}

Games::Button::~Button()
{

}

Games::Button::TYPE Games::Button::getType() const
{
    return (this->_type);
}

Arcade::Sprites_t Games::Button::getSprite() const
{
    return (this->_sprite);
}

std::string Games::Button::getFormattedData()
{
    return ("");
};

void Games::Button::addString(std::string str)
{

}

void Games::Button::removeString(size_t count)
{

}

std::string Games::Button::getSelected()
{
    return ("");
}

std::string Games::Button::getDetails()
{
    return ("");
}

void Games::Button::refreshSelector()
{

}

std::string Games::Button::getBest()
{
    return ("");
}
