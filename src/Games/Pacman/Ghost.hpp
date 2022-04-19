/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include "Player.hpp"
#include "Pacman.hpp"
#include <iostream>
#include <algorithm>

namespace Games {

    class Pacman;

    class Ghost {
        public:
            Ghost(int color, std::string map, Pacman *pacman);
            ~Ghost();

            Arcade::Sprites_t getGhost(bool endGame, bool startGhost);
            void walk();
            void walkDead();
            void walkFront(int pixWalk);
            void exitSpawn(int pixWalk);
            bool haveWall(int x, int y);
            void setStart(bool start);
            void animate();
            void findNewDir();
            void teleportation();
            bool haveCollision(std::pair<int, int> pacman);
            void startInactifClock();

        private:
            int _color;
            int _dir;
            Arcade::Sprites_t _ghost;
            std::pair<int, int> _startPos;
            std::pair<int, int> _pos;
            std::string _map;
            bool _start;
            std::shared_ptr<Pclock> _animationTime;
            std::shared_ptr<Pclock> _inactifClock;
            bool _isInactif;
            bool _isAlive;
            Pacman *_pacman;
            std::shared_ptr<Pclock> _timeToRespawn;
            int diviseRespown;
            bool startGhost;
    };

}

#endif /* !GHOST_HPP_ */
