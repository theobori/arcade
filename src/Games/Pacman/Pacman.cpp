/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

Games::Pacman::Pacman()
{
    this->_functions = {
        {Arcade::KeyState::Up, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Right, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Down, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Left, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::R, KEY_FUNC_CTOR(resetGame)}
    };
    this->_maps = this->my_get_file("./assets/pacman/map.txt");
    this->initGame();
}

void Games::Pacman::initGame()
{
    this->_pacman = std::make_shared<Player>(this->_maps);
    this->_redGhost = std::make_shared<Ghost>(0, this->_maps, this);
    this->_pinkGhost = std::make_shared<Ghost>(1, this->_maps, this);
    this->_blueGhost = std::make_shared<Ghost>(2, this->_maps, this);
    this->_orangeGhost = std::make_shared<Ghost>(3, this->_maps, this);
    this->_mapIsLoad = false;
    this->_endGame = false;
    this->_ghostInactif = false;
    this->_ghostInactifClock = std::make_shared<Pclock>(10);
    this->_speed = std::make_shared<Pclock>(0.008);
    this->_timeGhost = std::make_shared<Pclock>(10);
    this->_scoreText = {"", 32 * 18, 32 * 2, {0, 0, 255, 255}, 40, "assets/fonts/cool.ttf", 0};
    this->_score = 0;
    this->_startGhost = false;
}

void Games::Pacman::deleteGame()
{
    this->_sprites.clear();
    this->_texts.clear();
    this->_shapes.clear();
    this->_mapShape.clear();
    this->_dostShape.clear();
}

void Games::Pacman::resetGame(Arcade::KeyEvent_t event)
{
    this->deleteGame();
    this->initGame();
}

Games::Pacman::~Pacman()
{
}

void Games::Pacman::update()
{
    if (!this->_speed.get()->check())
        return;
    this->_shapes.clear();
    this->_sprites.clear();
    this->displayMaps();
    if (this->_dostShape.size() == 0 && !this->_endGame) {
        this->_endGame = true;
        this->saveScore();
    }
    if (!this->_endGame) {
        this->_pacman.get()->walk();
        this->teleportation();
        this->checkDots();
        this->_sprites["pacman"] = this->_pacman.get()->getPacman();
    }
    this->updateGhost();
    this->displayScore();
}

void Games::Pacman::updateGhost()
{
    if (this->_timeGhost.get()->check())
        this->_startGhost = true;
    this->_redGhost->setStart(true);
    this->_pinkGhost->setStart(true);
    this->_blueGhost->setStart(true);
    this->_orangeGhost->setStart(true);
    this->_sprites["redGhost"] = this->_redGhost.get()->getGhost(this->_endGame, this->_startGhost);
    this->_sprites["pinkGhost"] = this->_pinkGhost.get()->getGhost(this->_endGame, this->_startGhost);
    this->_sprites["blueGhost"] = this->_blueGhost.get()->getGhost(this->_endGame, this->_startGhost);
    this->_sprites["orangeGhost"] = this->_orangeGhost.get()->getGhost(this->_endGame, this->_startGhost);
    if (this->_endGame)
        return;
    if (this->_redGhost.get()->haveCollision(this->_pacman.get()->getPos()) || 
    this->_pinkGhost.get()->haveCollision(this->_pacman.get()->getPos()) ||
    this->_blueGhost.get()->haveCollision(this->_pacman.get()->getPos()) ||
    this->_orangeGhost.get()->haveCollision(this->_pacman.get()->getPos())) {
        this->_endGame = true;
        this->saveScore();
    }
}

void Games::Pacman::arrow(Arcade::KeyEvent_t event)
{
    if (event.key == Arcade::KeyState::Up)
        this->_pacman.get()->setDir(0);
    if (event.key == Arcade::KeyState::Right)
        this->_pacman.get()->setDir(1);
    if (event.key == Arcade::KeyState::Down)
        this->_pacman.get()->setDir(2);
    if (event.key == Arcade::KeyState::Left)
        this->_pacman.get()->setDir(3);
}

void Games::Pacman::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    for (const auto it : event) {
        if (this->_functions.count(it.key))
            this->_functions[it.key](this, it);
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::Pacman::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::Pacman::getSprites()
{
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::Pacman::getTexts()
{
    return (this->_texts);
}

std::pair<int, int> Games::Pacman::getSizeWindow()
{
    return (std::pair<int, int>(32 * 40, 32 * 30));
}

std::string Games::Pacman::my_get_file(std::string filename)
{
    std::string contentFile;
    std::stringstream sstr;
    std::ifstream f(filename, std::ios::in);

    sstr << f.rdbuf();
    contentFile = sstr.str();
    f.close();
    return (contentFile);
}

void Games::Pacman::teleportation()
{
    std::pair<int, int> tpLeft = {32 * 10, 32 * 13};
    std::pair<int, int> tpRight = {32 * 30, 32 * 13};
    std::pair<int, int> pacman = this->_pacman.get()->getPos();

    if (pacman.first == tpLeft.first && pacman.second == tpLeft.second) {
        this->_pacman.get()->setPos(tpRight);
    } else if (pacman.first == tpRight.first && pacman.second == tpRight.second) {
        this->_pacman.get()->setPos(tpLeft);
    }
}

void Games::Pacman::displayScore()
{
    this->_scoreText.text = ("Score : " + std::to_string(this->_score));
    this->_texts["score"] = this->_scoreText;
}

void Games::Pacman::saveScore()
{
    std::string name = this->my_get_file("./assets/name.txt");
    std::string fileContent = this->my_get_file("./assets/pacman/scores.txt");
    std::ofstream score;

    score.open("./assets/pacman/scores.txt");
    score << fileContent << "\n-\n" << name << "\n" << this->_score;
    score.close();
}

void Games::Pacman::incrementScore(int incr)
{
    this->_score += incr;
}

std::pair<int, int> Games::Pacman::getSizePixel()
{
    std::pair <int, int> pixelSize(32, 32);
    return (pixelSize);
}

extern "C" {
    std::shared_ptr<Games::IGameModule> create()
    {
        return (std::make_shared<Games::Pacman>());
    }
}