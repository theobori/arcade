/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Core
*/

#ifndef __CORE_HPP__
    #define __CORE_HPP__

    #include <iostream>
    #include <regex>
    #include <ctime>

    #include "DLLoader.hpp"
    #include "../Games/IGameModule.hpp"
    #include "../Graphicals/IDisplayModule.hpp"
    #include "Select.hpp"
    #include "Pclock.hpp"
    #include "../Utils/Available/Games.hpp"
    #include "../Utils/Available/Graphics.hpp"

    #define REFRESH_TIME 0.01

namespace Arcade {
    class Core {
        public:
            Core();
            ~Core();

            void CoreLoop();
            void update();

            void init();
            void loadGames();
            void loadGraphics();

            DLLoader getLoader() const;
            void initGraphics(std::string name);

            bool hasChangedGame(KeyState key);
            bool hasChangedLib(KeyState key);

            void updateLib();
            void updateGame();

            void eventListener(std::vector<Arcade::KeyEvent_t> keyEvents);
        
            bool isGameMenu();
            void goToMenu();
            void menuMirroring(KeyState key);
            void menuMirroringSelectors(KeyState key);
            void menuMirroringButtons(KeyState key);
            void menuListener(Arcade::KeyEvent_t event);

        private:
            DLLoader _loader;

            Select<std::shared_ptr<Games::IGameModule>> _games;
            Select<std::shared_ptr<Libs::IDisplayModule>> _graphics;

            Utils::Games _gamesAvailable;
            Utils::Graphics _graphicsAvailable;

            bool _releaseKey;

            // Menu mirror
            int _menuButton;
            int _menuGame;
            int _menuGraphic;

            // Current lib and game
            Libs::IDisplayModule *_currentGraphic;
            Games::IGameModule *_currentGame;

            bool _loopRunning;
            std::shared_ptr<Pclock> _clock;
    };
}

#endif /* !CORE_HPP_ */
