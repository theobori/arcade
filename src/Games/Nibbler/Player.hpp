/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <list>
    #include "../GameModule.hpp"
    #include "Body.hpp"
    #include <memory>

namespace Games {
    class Player {
        public:
            Player();
            ~Player();

            void displayPlayer();
            Arcade::Sprites_t getHead();
            std::vector<std::shared_ptr<Body>> getBody();
            void update();
            void updateBody();
            void addBody();
            void animate();
            void walk();
            void setDir(int dir);
            void changeDir();
            bool haveColition();
            std::vector<std::pair<int, int>> getPath();

        private:
            int _length;
            Arcade::Sprites_t _head;
            int _dir;
            int _saveDir;
            std::vector<std::shared_ptr<Body>> _body;
            std::vector<std::pair<int, int>> _path;
    };
}

#endif /* !PLAYER_HPP_ */
