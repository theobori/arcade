/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** GameSave
*/

#include "GameData.hpp"

Games::GameData::GameData(std::string path)
{
    this->_pathToSave = path;

    this->updateSave();
}

Games::GameData::GameData()
{
    throw GamesError("You must enter a game name", "Invalid name");
}

Games::GameData::~GameData()
{

}

void Games::GameData::addGameSave(std::string username, unsigned int score)
{
    GameSave save = GameSave();

    save.username = username;
    save.score = score;
    this->_saves.insert(this->_saves.begin(), save);
}

std::vector<Games::GameSave> Games::GameData::getGameSaves() const
{
    return (this->_saves);
}

Games::GameSave Games::GameData::getGameSave(std::size_t index) const
{
    if (index >= this->_saves.size())
        throw GamesError("Index too high", "Invalid index");

    return (this->_saves.at(index));
}

Games::GameSave Games::GameData::getHighScore() const
{
    GameSave bestSave = {};
    size_t maxScore = 0;

    for (const auto save : this->_saves) {
        if (save.score >= maxScore) {
            maxScore = save.score;
            bestSave = save;
        }
    }
    return (bestSave);
}

std::vector<std::string> Games::GameData::split(std::string data, std::string separator)
{
    int start = 0;
    int end = data.find(separator);
    std::vector<std::string> ret;
    std::string dataToAdd = "";

    while (end != -1) {
        dataToAdd = data.substr(start, end - start);

        if (dataToAdd.size() == 0)
            continue;

        ret.push_back(dataToAdd);
        start = end + separator.size();
        end = data.find(separator, start);
    }

    dataToAdd = data.substr(start, end - start);
    if (dataToAdd.size() == 0)
        return (ret);
    ret.push_back(dataToAdd);

    return (ret);
}

bool Games::GameData::isDigits(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) 
            return (false);
    }

    return (true);
}

void Games::GameData::updateSave()
{
    std::string contentFile;
    std::stringstream sstr;
    std::ifstream f(this->_pathToSave, std::ios::in);
    std::vector<std::string> tmp;

    if (f.is_open() == false)
        return;

    this->_saves = {};
    sstr << f.rdbuf();
    contentFile = sstr.str();
    f.close();

    for (auto data : Games::GameData::split(contentFile, "\n-\n")) {
        tmp = Games::GameData::split(data, "\n");
        if (tmp.size() != 2)
            continue;
        if (tmp.at(0).size() == 0 || tmp.at(1).size() == 0)
            continue;
        if (Games::GameData::isDigits(tmp.at(1)) == false)
            continue;
        this->addGameSave(tmp.at(0), std::stoi(tmp.at(1)));
    }
}
