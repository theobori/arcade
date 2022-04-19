/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Pacman
*/

#ifndef __PACMAN_HPP__
    #define __PACMAN_HPP__

    #include <memory>
    #include <map>
    #include <functional>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>

    #include "../GameModule.hpp"
    #include "Player.hpp"
    #include "Ghost.hpp"

    #define KEY_FUNC_CTOR(func) \
        [](Games::Pacman *ptr, Arcade::KeyEvent_t event) -> void { \
        ptr->func(event); \
    }

namespace Games {
    class Ghost;

    class Pacman : public GameModule{
        public:
            Pacman();
            ~Pacman();

            void update();

            void initGame();
            void deleteGame();
            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            std::string my_get_file(std::string filename);
            void updateGhost();
            void loadMaps();
            void displayMaps();
            void checkDots();
            void arrow(Arcade::KeyEvent_t event);
            void teleportation();
            void resetGame(Arcade::KeyEvent_t event);
            void incrementScore(int incr);
            void displayScore();
            void saveScore();
            std::pair<int, int> getSizePixel();

        private:
            std::unordered_map<std::string, Arcade::Rect_t> _shapes;
            std::unordered_map<std::string, Arcade::Sprites_t> _sprites;
            std::unordered_map<std::string, Arcade::Text_t> _texts;
            std::map<Arcade::KeyState, std::function<void(Games::Pacman *, Arcade::KeyEvent_t)>> _functions;
            std::string _maps;
            std::shared_ptr<Player> _pacman;
            std::shared_ptr<Ghost> _redGhost;
            std::shared_ptr<Ghost> _pinkGhost;
            std::shared_ptr<Ghost> _blueGhost;
            std::shared_ptr<Ghost> _orangeGhost;
            std::vector<Arcade::Rect_t> _mapShape;
            std::vector<Arcade::Sprites_t> _dostShape;
            Arcade::Rect_t _door;
            bool _mapIsLoad;
            bool _startGhost;
            std::shared_ptr<Pclock> _timeGhost;
            bool _endGame;
            int _score;
            bool _ghostInactif;
            std::shared_ptr<Pclock> _ghostInactifClock;
            std::shared_ptr<Pclock> _speed;
            Arcade::Text_t _scoreText;
    };
}

#endif /* !PACMAN_HPP_ */
