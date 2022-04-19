/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Menu
*/

#ifndef __MENU_HPP__
    #define __MENU_HPP__

    #include <memory>
    #include <map>
    #include <functional>

    #include "../GameModule.hpp"
    #include "../Select.hpp"
    #include "./Button/Button.hpp"
    #include "./Button/OneClick.hpp"
    #include "./Button/GameSelector.hpp"
    #include "./Button/LibSelector.hpp"
    #include "./Button/Input.hpp"
    #include "../../Utils/Available/Games.hpp"
    #include "../../Utils/Available/Graphics.hpp"

    #define KEY_FUNC_CTOR(func) \
        [](Games::Menu *ptr, Arcade::KeyEvent_t event) -> void { \
        ptr->func(event); \
    }

namespace Games {
    class Menu : public GameModule {
        public:
            Menu();
            ~Menu();

            void update();

            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
    
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);

            void initButtons();
            void init();
            void updateButtons();
            
            void previousButton(Arcade::KeyEvent_t event);
            void nextButton(Arcade::KeyEvent_t event);
            void previousSelector(Arcade::KeyEvent_t event);
            void nextSelector(Arcade::KeyEvent_t event);
            void play(Arcade::KeyEvent_t event);


            void setCursor();
            bool typeInput(Arcade::KeyState key);

            std::string getButtonName();

            void updateScores();
            void refreshScoresData();

        private:
            std::unordered_map<std::string, Arcade::Rect_t> _shapes;
            std::unordered_map<std::string, Arcade::Sprites_t> _sprites;
            std::unordered_map<std::string, Arcade::Text_t> _texts;
            std::map<Arcade::KeyState, std::function<void(Games::Menu *, Arcade::KeyEvent_t)>> _functions;

            Select<Games::IButton *> _buttons;
            std::map<Arcade::KeyState, std::string> _keyToString;

            // Unique sprites
            Arcade::Sprites_t _logo;
            Arcade::Sprites_t _cursorDefault;
            Arcade::Sprites_t _cursorSelector;
            Arcade::Sprites_t _cursorInput;
            Arcade::Sprites_t _scores;

            // Scores
            std::vector<std::string> _lastScores;
            std::string _highScore;

            // Smart pointers for buttons
            std::shared_ptr<Games::OneClick> _playButton;
            std::shared_ptr<Games::Input> _inputButton;
            std::shared_ptr<Games::GameSelector> _gameSelector;
            std::shared_ptr<Games::LibSelector> _libSelector;
            std::shared_ptr<Games::OneClick> _quitButton;
    };
}

extern "C" {
    std::shared_ptr<Games::IGameModule> create()
    {
        return (std::make_shared<Games::Menu>());
    }
}

#endif /* !Menu_HPP_ */
