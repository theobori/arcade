/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Ghost
*/

#include "Ghost.hpp"
#include "Pclock.hpp"

Games::Ghost::Ghost(int color, std::string map, Pacman *pacman)
{
    this->_color = color;
    this->_dir = -1;
    this->_map = map;
    this->_start = false;
    this->_animationTime = std::make_shared<Pclock>(0.1);
    this->_pacman = pacman;
    this->_isAlive = true;
    this->_timeToRespawn = std::make_shared<Pclock>(4);
    std::srand(std::time(nullptr));
    Arcade::SpriteRect_t rect = {0, color * 32, 32, 32, 32 * 8, 32 * 6};
    if (color == 0)
        this->_startPos = {32 * 19, 32 * 14};
    if (color == 1)
        this->_startPos = {32 * 20, 32 * 14};
    if (color == 2)
        this->_startPos = {32 * 21, 32 * 14};
    if (color == 3)
        this->_startPos = {32 * 20, 32 * 13};
    Arcade::Color_t bg = {255, 0, 0, 0};
    Arcade::Color_t text = {0, 0, 0, 0};
    this->_ghost = {this->_startPos.first, this->_startPos.second, "./assets/pacman/ghost", rect, text, bg, 1};
    this->_inactifClock = std::make_shared<Pclock>(10);
    this->_isInactif = false;
    this->diviseRespown = 100;
    this->startGhost = false;
}

Games::Ghost::~Ghost()
{
}

Arcade::Sprites_t Games::Ghost::getGhost(bool endGame, bool startGhost)
{
    if (startGhost)
        this->startGhost = true;
    if (!endGame) {
        this->animate();
        this->walk();
    }
    return (this->_ghost);
}

void Games::Ghost::animate()
{
    if (!this->_animationTime.get()->check())
        return;
    if (this->_inactifClock.get()->check())
        this->_isInactif = false;
    int frame = (this->_ghost.rect.x % 64 > 0) ? 0 : 32;

    this->_ghost.bg.r = 255;
    this->_ghost.bg.b = 0;
    this->_ghost.rect.x = std::max(this->_dir * 64, 0) + frame;
    this->_ghost.rect.y = this->_color * 32;
    if (this->_isInactif) {
        this->_ghost.rect.x = frame;
        this->_ghost.rect.y = 32 * 4;
        this->_ghost.bg.r = 0;
        this->_ghost.bg.b = 255;
    }
    if (this->_isAlive == false)
        this->_ghost.rect.y = 32 * 5;
}

void Games::Ghost::walkDead()
{
    this->_ghost.x -= (this->_ghost.x - this->_startPos.first) / this->diviseRespown;
    this->_ghost.y -= (this->_ghost.y - this->_startPos.second) / this->diviseRespown;
    this->_pos.first = this->_ghost.x;
    this->_pos.second = this->_ghost.y;
    this->diviseRespown -= 1;
    if (this->_ghost.x == this->_startPos.first && this->_ghost.y == this->_startPos.second) {
        this->_isAlive = true;
        this->_isInactif = false;
        this->diviseRespown = 100;
    }
}

void Games::Ghost::walk()
{
    int pixWalk = 2;

    if (!this->_start)
        return;
    if (!this->_isAlive) {
        this->walkDead();
        return;
    } else {
        this->walkFront(pixWalk);
        this->teleportation();
    }
    this->_pos.first = this->_ghost.x;
    this->_pos.second = this->_ghost.y;
}

void Games::Ghost::walkFront(int pixWalk)
{
    if (this->_ghost.x % 32 == 0 && this->_ghost.y % 32 == 0)
        this->findNewDir();
    if (this->_dir == 0 && !this->haveWall(this->_ghost.x, this->_ghost.y - pixWalk)) {
        this->_ghost.y -= pixWalk;
        return;
    }
    if (this->_dir == 1 && !this->haveWall(this->_ghost.x + pixWalk, this->_ghost.y)) {
        this->_ghost.x += pixWalk;
        return;
    }
    if (this->_dir == 2 && !this->haveWall(this->_ghost.x, this->_ghost.y + pixWalk)) {
        this->_ghost.y += pixWalk;
        return;
    }
    if (this->_dir == 3 && !this->haveWall(this->_ghost.x - pixWalk, this->_ghost.y)) {
        this->_ghost.x -= pixWalk;
        return;
    }
}

void Games::Ghost::exitSpawn(int pixWalk)
{
    if (this->_ghost.x < 32 * 20) {
        this->_ghost.x += pixWalk;
        this->_dir = 1;
        return;
    }
    if (this->_ghost.x > 32 * 20) {
        this->_ghost.x -= pixWalk;
        this->_dir = 3;
        return;
    }
    this->_dir = 0;
    this->_ghost.y -= pixWalk;
}

void Games::Ghost::findNewDir()
{
    int random = std::rand();
    std::vector<int> list = {};

    if (!this->haveWall(this->_ghost.x, this->_ghost.y - 1) && this->_dir != 2)
        list.push_back(0);
    if (!this->haveWall(this->_ghost.x + 1, this->_ghost.y) && this->_dir != 3)
        list.push_back(1);
    if (!this->haveWall(this->_ghost.x, this->_ghost.y + 1) && this->_dir != 0)
        list.push_back(2);
    if (!this->haveWall(this->_ghost.x - 1, this->_ghost.y) && this->_dir != 1)
        list.push_back(3);
    for (const auto it: list) {
        if (it == this->_dir)
            list.push_back(this->_dir);
    }
    this->_dir = list[random % list.size()];
}

bool Games::Ghost::haveWall(int x, int y)
{
    int orX = 32 * 10;
    int orY = 32 * 4;
    int len = this->_map.length();

    int calX = x - orX;
    int calY = y - orY;

    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    if (!this->startGhost && this->_map[(calX / 32) + ((calY / 32) * 22)] == 'D')
        return (true);
    calX += 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    if (!this->startGhost && this->_map[(calX / 32) + ((calY / 32) * 22)] == 'D')
        return (true);
    calY += 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    if (!this->startGhost && this->_map[(calX / 32) + ((calY / 32) * 22)] == 'D')
        return (true);
    calX -= 31;
    if (this->_map[(calX / 32) + ((calY / 32) * 22)] == 'X')
        return (true);
    if (!this->startGhost && this->_map[(calX / 32) + ((calY / 32) * 22)] == 'D')
        return (true);
    return (false);
}

void Games::Ghost::setStart(bool start)
{
    this->_start = start;
}

void Games::Ghost::teleportation()
{
    std::pair<int, int> tpLeft = {32 * 10, 32 * 13};
    std::pair<int, int> tpRight = {32 * 30, 32 * 13};
    std::pair<int, int> ghost = {this->_ghost.x, this->_ghost.y};

    if (ghost.first == tpLeft.first && ghost.second == tpLeft.second) {
        this->_ghost.x = tpRight.first;
        this->_ghost.y = tpRight.second;
    } else if (ghost.first == tpRight.first && ghost.second == tpRight.second) {
        this->_ghost.x = tpLeft.first;
        this->_ghost.y = tpLeft.second;
    }
}

bool Games::Ghost::haveCollision(std::pair<int, int> pacman)
{
    if (!this->_isAlive)
        return (false);
    if (std::abs(pacman.first - this->_pos.first) < 10 && pacman.second == this->_pos.second && this->_isInactif == false)
        return (true);
    if (std::abs(pacman.second - this->_pos.second) < 10 && pacman.first == this->_pos.first && this->_isInactif == false)
        return (true);
    if (std::abs(pacman.first - this->_pos.first) < 10 && pacman.second == this->_pos.second) {
        this->_pacman->incrementScore(100);
        this->_isAlive = false;
        this->_timeToRespawn.get()->reset();
    }
    if (std::abs(pacman.second - this->_pos.second) < 10 && pacman.first == this->_pos.first) {
        this->_pacman->incrementScore(100);
        this->_isAlive = false;
        this->_timeToRespawn.get()->reset();
    }
    return (false);
}

void Games::Ghost::startInactifClock()
{
    this->_inactifClock.get()->reset();
    this->_isInactif = true;
}