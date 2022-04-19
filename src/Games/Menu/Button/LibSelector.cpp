/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** selector
*/

#include "LibSelector.hpp"


Games::LibSelector::LibSelector(Arcade::Sprites_t sprite)
: Button(Button::TYPE::LIB_SELECTOR, sprite)
{
}

Games::LibSelector::~LibSelector()
{
}

std::string Games::LibSelector::getFormattedData()
{
    std::string ret = "";

    ret = "GRAPHIC: " + this->_data.getCurrent().second;
    return (ret);
}

Games::Select<std::string> &Games::LibSelector::getData()
{
    return (this->_data);
}

std::string Games::LibSelector::getSelected()
{
    return (this->_data.getCurrent().second);
}

std::string Games::LibSelector::getDetails()
{
    return ("");
}