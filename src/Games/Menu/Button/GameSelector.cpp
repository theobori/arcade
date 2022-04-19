/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** selector
*/

#include "GameSelector.hpp"

Games::GameSelector::GameSelector(Arcade::Sprites_t sprite)
: Button(Button::TYPE::GAME_SELECTOR, sprite)
{
}

Games::GameSelector::~GameSelector()
{
}

std::string Games::GameSelector::getFormattedData()
{
    std::string ret = "";
    Games::GameData select = this->_data.getCurrent().second;

    ret += "GAME: " + this->_data.getCurrent().first;
    return (ret);
}

std::string Games::GameSelector::getDetails()
{
    std::string ret = "";
    Games::GameData select = this->_data.getCurrent().second;
    std::vector<Games::GameSave> saves = select.getGameSaves();

    if (saves.size() == 0)
        return ("NO SCORES");
    
    for (unsigned int i = 0; i < (saves.size()) && i < 10; i++) {
        ret += saves.at(i).username + " - ";
        ret += std::to_string(saves.at(i).score) + "\n";
    }
    return (ret);
}

std::string Games::GameSelector::getBest()
{
    Games::GameSave bestSave = this->_data.getCurrent().second.getHighScore();
    std::string ret = "";

    if (bestSave.username.size() == 0 && bestSave.score == 0)
        return ("NO HIGHSCORES");

    ret += bestSave.username + " - ";
    ret += std::to_string(bestSave.score);

    return (ret);
}

Games::Select<Games::GameData> &Games::GameSelector::getData()
{
    return (this->_data);
}

std::string Games::GameSelector::getSelected()
{
    return (this->_data.getCurrent().first);
}

void Games::GameSelector::refreshSelector()
{
    this->_data.getCurrent().second.updateSave();
}
