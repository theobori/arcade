/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Player
*/

#include "Player.hpp"

Games::Player::Player()
{
    int lenght = 0;
    Arcade::SpriteRect_t rect = {0, 0, 64, 64, 64, 64};
    Arcade::Color_t text = {0, 0, 0, 0};
    Arcade::Color_t bg = {255, 0, 0, 0};
    this->_head = {32 * 20, 32 * 16, "./assets/nibbler/head", rect, text, bg, 1};
    this->_dir = 0;
    this->_saveDir = -1;
    this->addBody();
    this->addBody();
    this->addBody();
    this->addBody();

    this->_path.insert(this->_path.begin(), std::make_pair(32 * 20 + 16, 32 * 20));
    this->_path.insert(this->_path.begin(), std::make_pair(32 * 20 + 16, 32 * 19));
    this->_path.insert(this->_path.begin(), std::make_pair(32 * 20 + 16, 32 * 18));
    this->_path.insert(this->_path.begin(), std::make_pair(32 * 20 + 16, 32 * 17));
}

Arcade::Sprites_t Games::Player::getHead()
{
    return (this->_head);
}

std::vector<std::shared_ptr<Games::Body>> Games::Player::getBody()
{
    return (this->_body);
}

Games::Player::~Player()
{
}

void Games::Player::displayPlayer()
{
}

void Games::Player::update()
{
    this->walk();
    this->animate();
}

void Games::Player::updateBody()
{
    int x = this->_head.x;
    int y = this->_head.y;

    int t = 0;

    for (auto it : this->_body) {
        it.get()->walk(this->_path[t]);
        x = it.get()->getX();
        y = it.get()->getY();
        t++;
    }
}

void Games::Player::addBody()
{
    int x = 0;
    int y = 0;

    if (this->_body.size() == 0) {
        x = this->_head.x + 16;
        y = this->_head.y + 16;
    } else {
        x = this->_body.back()->getX();
        y = this->_body.back()->getY();
    }
    std::shared_ptr<Body> newBody = std::make_shared<Body>(x, y + 32, this->_body.size());
    this->_body.push_back(newBody);
}

void Games::Player::animate()
{
    this->_head.rect.x = this->_dir * 64;
}

void Games::Player::setDir(int dir)
{
    if (dir != this->_dir && dir % 2 != this->_dir % 2) {
        this->_saveDir = dir;
    }
}

void Games::Player::changeDir()
{
    if (this->_saveDir == 0 && this->_head.x % 64 == 0) {
        this->_dir = 0;
        this->_saveDir = -1;
    }
    if (this->_saveDir == 1 && this->_head.y % 64 == 0) {
        this->_dir = 1;
        this->_saveDir = -1;
    }
    if (this->_saveDir == 2 && this->_head.x % 64 == 0) {
        this->_dir = 2;
        this->_saveDir = -1;
    }
    if (this->_saveDir == 3 && this->_head.y % 64 == 0) {
        this->_dir = 3;
        this->_saveDir = -1;
    }
}

void Games::Player::walk()
{
    int speed = 4;
    if (this->_head.x % 32 == 0 && this->_head.y % 32 == 0) {
        this->_path.insert(this->_path.begin(), std::make_pair(this->_head.x + 16, this->_head.y + 16));
    }
    if (this->_path.size() > this->_body.size())
        this->_path.pop_back();

    this->changeDir();
    if (this->_dir == 0)
        this->_head.y -= speed;
    if (this->_dir == 1)
        this->_head.x += speed;
    if (this->_dir == 2)
        this->_head.y += speed;
    if (this->_dir == 3)
        this->_head.x -= speed;
}

bool Games::Player::haveColition()
{
    int pos = 0;

    for (auto it : this->_path) {
        if (this->_dir == 0 && this->_head.y - 16 == it.second && this->_head.x + 16 == it.first) {
            return (true);
        }
        if (this->_dir == 1 && this->_head.x + 16 == it.first && this->_head.y + 16 == it.second) {
            return (true);
        }
        if (this->_dir == 2 && this->_head.y + 16 == it.second && this->_head.x - 16 == it.first) {
            return (true);
        }
        if (this->_dir == 3 && this->_head.x - 16 == it.first  && this->_head.y - 16 == it.second) {
            return (true);
        }
        pos++;
    }
    return (false);
}

std::vector<std::pair<int, int>> Games::Player::getPath()
{
    return (this->_path);
}