/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "../GameModule.hpp"
    #include "Pclock.hpp"
    #include <memory>

namespace Games {
    class Player {
        public:
            Player(std::string map);
            Player();
            ~Player();

            Arcade::Sprites_t getPacman();
            void walk();
            void setDir(int dir);
            bool haveWall(int x, int y);
            void checkDir();
            std::pair<int, int> getPos();
            void setPos(std::pair<int, int>);
    
        private:
            Arcade::Sprites_t _pacman;
            int _dir;
            std::string _map;
            int _moveSave;
            std::pair<int, int> _pos;
            std::shared_ptr<Pclock> _animation;
    };
}

#endif /* !PLAYER_HPP_ */
