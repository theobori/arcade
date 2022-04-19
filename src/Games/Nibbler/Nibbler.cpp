/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Games::Nibbler::Nibbler()
{
    this->_functions = {
        {Arcade::KeyState::Up, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Right, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Down, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::Left, KEY_FUNC_CTOR(arrow)},
        {Arcade::KeyState::R, KEY_FUNC_CTOR(resetGame)}
    };
    Arcade::SpriteRect_t rect = {0, 0, 32 * 40, 32 * 30, 32 * 40, 32 * 30};
    Arcade::Color_t text = {0, 0, 0, 0};
    Arcade::Color_t bg = {0, 255, 0, 0};

    this->_bg = {0, 0, "./assets/nibbler/bg", rect, text, bg, 0};
    this->initGame();
    std::srand(std::time(nullptr));
    this->_score = {"", 32 * 19 + 16, 32 * 1 - 10, {0, 0, 255, 255}, 40, "assets/fonts/cool.ttf", 1};
}

Games::Nibbler::~Nibbler()
{
}

void Games::Nibbler::initGame()
{
    this->_player = std::make_shared<Player>();
    this->_updateTime = std::make_shared<Pclock>(0.006);
    this->createApple();
    this->gameOver = false;
}
void Games::Nibbler::deleteGame()
{
    this->_shapes.clear();
    this->_sprites.clear();
    this->_texts.clear();
}

void Games::Nibbler::resetGame(Arcade::KeyEvent_t event)
{
    this->deleteGame();
    this->initGame();
}

void Games::Nibbler::update()
{
    if (!this->_updateTime.get()->check())
        return;
    if (!this->gameOver) {
        this->_player.get()->update();
        this->checkEat();
        this->_player.get()->updateBody();
    }

    if (!this->gameOver) {
        this->checkColition();
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::Nibbler::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::Nibbler::getSprites()
{
    this->_sprites["head"] = this->_player.get()->getHead();
    this->_sprites["bg"] = this->_bg;
    int t = 0;
    for (auto it : this->_player.get()->getBody()) {
        this->_sprites["body" + std::to_string(t)] = it->getBody();
        t++;
    }
    this->_sprites["apple"] = this->_apple.get()->getApple();
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::Nibbler::getTexts()
{
    this->_texts["score"] = this->displayScore();
    return (this->_texts);
}

std::pair<int, int> Games::Nibbler::getSizeWindow()
{
    return (std::pair<int, int>(32 * 40, 32 * 30));
}

void Games::Nibbler::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    for (const auto it : event) {
        if (this->_functions.count(it.key))
            this->_functions[it.key](this, it);
    }
}

void Games::Nibbler::arrow(Arcade::KeyEvent_t event)
{
    if (event.key == Arcade::KeyState::Up)
        this->_player.get()->setDir(0);
    if (event.key == Arcade::KeyState::Right)
        this->_player.get()->setDir(1);
    if (event.key == Arcade::KeyState::Down)
        this->_player.get()->setDir(2);
    if (event.key == Arcade::KeyState::Left)
        this->_player.get()->setDir(3);
}

void Games::Nibbler::createApple()
{
    std::srand(std::rand());
    int x = ((std::rand() % 18) + 1) * 64;
    int y = ((std::rand() % 13) + 1) * 64;

    for (const auto it : this->_player.get()->getPath()) {
        if (it.first - 16 == x && it.second - 16 == y) {
            this->createApple();
            return;
        }
    }
    if (((this->_player.get()->getHead().x / 32) * 32) == x && ((this->_player.get()->getHead().y / 32) * 32) == y) {
        this->createApple();
        return;
    }
    this->_apple = std::make_shared<Apple>(x, y);
}

void Games::Nibbler::checkEat()
{
    if (this->_player.get()->getHead().x != this->_apple.get()->getApple().x || this->_player.get()->getHead().y != this->_apple.get()->getApple().y)
        return;
    this->_player.get()->addBody();
    this->createApple();
}

void Games::Nibbler::checkColition()
{
    int nibX = this->_player.get()->getHead().x;
    int nibY = this->_player.get()->getHead().y;
    int size = 0;

    if (nibX > 32 * 36 || nibX < 32 * 2 || nibY > 32 * 26 || nibY < 32 * 2) {
        this->gameOver = true;
        this->saveScore();
    }
    if (this->_player.get()->haveColition()) {
        this->gameOver = true;
        this->saveScore();
    }
}

void Games::Nibbler::saveScore()
{
    std::string name = this->my_get_file("./assets/name.txt");
    std::string fileContent = this->my_get_file("./assets/nibbler/scores.txt");
    std::ofstream score;

    score.open("./assets/nibbler/scores.txt");
    score << fileContent << "\n-\n" << name << "\n" << this->_player.get()->getBody().size() - 4;
    score.close();
}

std::string Games::Nibbler::my_get_file(std::string filename)
{
    std::string content_file;
    std::stringstream sstr;
    std::ifstream f(filename, std::ios::in);

    sstr << f.rdbuf();
    content_file = sstr.str();
    f.close();
    return (content_file);
}

Arcade::Text_t Games::Nibbler::displayScore()
{
    this->_score.text = std::to_string(this->_player.get()->getBody().size() - 4);
    return (this->_score);
}

std::pair<int, int> Games::Nibbler::getSizePixel()
{
    std::pair <int, int> pixelSize(32, 32);
    return (pixelSize);
}