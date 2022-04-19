/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** GameModule
*/

#include "GameModule.hpp"

Games::GameModule::GameModule()
{

}

Games::GameModule::~GameModule()
{

}

void Games::GameModule::update()
{

}

std::unordered_map<std::string, Arcade::Rect_t> Games::GameModule::getShapes()
{
    return (std::unordered_map<std::string, Arcade::Rect_t>());
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::GameModule::getSprites()
{
    return (std::unordered_map<std::string, Arcade::Sprites_t>());
}

std::unordered_map<std::string, Arcade::Text_t> Games::GameModule::getTexts()
{
    return (std::unordered_map<std::string, Arcade::Text_t>());
}

std::pair<int, int> Games::GameModule::getSizeWindow()
{
    return (std::pair<int, int>());
}

void Games::GameModule::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{

}

int Games::GameModule::hCenter(int size, int ref)
{
    if (ref < size)
        return ((this->getSizeWindow().second - size) / 2);
    return ((ref - size) / 2);
}

int Games::GameModule::wCenter(int size, int ref)
{
    if (ref < size)
        return ((this->getSizeWindow().first - size) / 2);
    return ((ref - size) / 2);
}
std::pair<int, int> Games::GameModule::getSizePixel()
{
    return (std::pair<int, int> (32, 32));
}
