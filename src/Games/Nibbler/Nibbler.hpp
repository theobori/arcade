/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Nibbler
*/

#ifndef __NIBBLER_HPP__
    #define __NIBBLER_HPP__

    #include <memory>

    #include "../GameModule.hpp"
    #include "Maps.hpp"
    #include "Player.hpp"
    #include "Pclock.hpp"
    #include "Body.hpp"
    #include "Apple.hpp"
    #include <functional>
    #include <iostream>

    #define KEY_FUNC_CTOR(func) \
        [](Games::Nibbler *ptr, Arcade::KeyEvent_t event) -> void { \
        ptr->func(event); \
    }

namespace Games {

    class Nibbler : public GameModule {
        public:
            Nibbler();
            ~Nibbler();

            void initGame();
            void deleteGame();

            void update();

            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            void arrow(Arcade::KeyEvent_t event);
            void resetGame(Arcade::KeyEvent_t event);
            void createApple();
            void checkEat();
            void checkColition();
            void saveScore();
            Arcade::Text_t displayScore();
            std::string my_get_file(std::string filename);
            std::pair<int, int> getSizePixel();

            std::unordered_map<std::string, Arcade::Rect_t> _shapes;
            std::unordered_map<std::string, Arcade::Sprites_t> _sprites;
            std::unordered_map<std::string, Arcade::Text_t> _texts;

        private:
            std::shared_ptr<Player> _player;
            std::shared_ptr<Pclock> _updateTime;
            Arcade::Sprites_t _bg;
            std::shared_ptr<Apple> _apple;
            std::map<Arcade::KeyState, std::function<void(Games::Nibbler *, Arcade::KeyEvent_t)>> _functions;
            bool gameOver;
            Arcade::Text_t _score;
    };
}

extern "C" {
    std::shared_ptr<Games::IGameModule> create()
    {
        return (std::make_shared<Games::Nibbler>());
    }
}

#endif /* !NIBBLER_HPP_ */
