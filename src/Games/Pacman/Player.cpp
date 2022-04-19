/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Player
*/

#include "Player.hpp"

Games::Player::Player(std::string map)
{
    this->_map = map;
    Arcade::SpriteRect_t rect = {0, 0, 32, 32, 32 * 4, 32 * 4};
    Arcade::Color_t bg = {255, 255, 0, 1};
    Arcade::Color_t text = {255, 255, 255, 1};
    this->_pacman = {32 * 20, 32 * 16, "./assets/pacman/pacman", rect, text, bg, 1};
    this->_dir = -1;
    this->_moveSave = -1;
    this->_animation = std::make_shared<Pclock>(0.06);
}

Games::Player::Player()
{
    std::cerr << "error on Games::Player::Player creation" << std::endl;
}

Games::Player::~Player()
{
}

std::pair<int, int> Games::Player::getPos()
{
    return (this->_pos);
}

void Games::Player::walk()
{
    int pixWalk = 2;
    this->checkDir();

    if (this->_dir == 0 && !this->haveWall(this->_pacman.x, this->_pacman.y - pixWalk))
        this->_pacman.y -= pixWalk;
    if (this->_dir == 1 && !this->haveWall(this->_pacman.x + pixWalk, this->_pacman.y))
        this->_pacman.x += pixWalk;
    if (this->_dir == 2 && !this->haveWall(this->_pacman.x, this->_pacman.y + pixWalk))
        this->_pacman.y += pixWalk;
    if (this->_dir == 3 && !this->haveWall(this->_pacman.x - pixWalk, this->_pacman.y))
        this->_pacman.x -= pixWalk;
    this->_pos.first = this->_pacman.x;
    this->_pos.second = this->_pacman.y;
}

bool Games::Player::haveWall(int x, int y)
{
    int orX = 32 * 10;
    int orY = 32 * 4;
    int len = this->_map.length();

    int calX = x - orX;
    int calY = y - orY;

    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    calX += 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    calY += 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    calX -= 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    return (false);
}

Arcade::Sprites_t Games::Player::getPacman()
{
    if (this->_dir != -1)
        this->_pacman.rect.y = this->_dir * 32;
    else
        this->_pacman.rect.y = 32;
    if (!this->_animation.get()->check())
        return (this->_pacman);
    this->_pacman.rect.x = (32 + this->_pacman.rect.x) % 128;
    return (this->_pacman);
}

void Games::Player::setDir(int dir)
{
    this->_moveSave = -1;

    if (dir == 0 && !this->haveWall(this->_pacman.x, this->_pacman.y - 1)) {
        this->_dir = 0;
        return;
    }
    if (dir == 1 && !this->haveWall(this->_pacman.x + 1, this->_pacman.y)) {
        this->_dir = 1;
        return;
    }
    if (dir == 2 && !this->haveWall(this->_pacman.x, this->_pacman.y + 1)) {
        this->_dir = 2;
        return;
    }
    if (dir == 3 && !this->haveWall(this->_pacman.x - 1, this->_pacman.y)) {
        this->_dir = 3;
        return;
    }
    this->_moveSave = dir;
}

void Games::Player::checkDir()
{
    if (this->_moveSave == 0 && !this->haveWall(this->_pacman.x, this->_pacman.y - 1)) {
        this->_dir = 0;
        this->_moveSave == -1;
        return;
    }
    if (this->_moveSave == 1 && !this->haveWall(this->_pacman.x + 1, this->_pacman.y)) {
        this->_dir = 1;
        this->_moveSave == -1;
        return;
    }
    if (this->_moveSave == 2 && !this->haveWall(this->_pacman.x, this->_pacman.y + 1)) {
        this->_dir = 2;
        this->_moveSave == -1;
        return;
    }
    if (this->_moveSave == 3 && !this->haveWall(this->_pacman.x - 1, this->_pacman.y)) {
        this->_dir = 3;
        this->_moveSave == -1;
        return;
    }
}

void Games::Player::setPos(std::pair<int, int> pos)
{
    this->_pacman.x = pos.first;
    this->_pacman.y = pos.second;
    this->_pos.first = this->_pacman.x;
    this->_pos.second = this->_pacman.y;
}