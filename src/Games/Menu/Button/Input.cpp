/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** input
*/

#include "Input.hpp"

Games::Input::Input(Arcade::Sprites_t sprite):
Button(Games::Button::TYPE::INPUT, sprite)
{
    this->_text = "USERNAME";
}

Games::Input::~Input()
{

}

std::string Games::Input::getFormattedData()
{
    return (this->_text);
}

void Games::Input::addString(std::string str)
{
    if (this->_text.size() >= 10)
        return;
    this->_text += str;
}

void Games::Input::removeString(size_t count)
{
    std::size_t size = this->_text.size();

    if (count > size)
        return;
    this->_text = this->_text.substr(0, size - count);
}
