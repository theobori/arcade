/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** GameModule
*/

#ifndef __GAMEMODULE_HPP__
    #define __GAMEMODULE_HPP__

    #include "IGameModule.hpp"

namespace Games {
    class GameModule : public IGameModule {
        public:
            GameModule();
            ~GameModule();

            void update();

            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            
            int hCenter(int size, int ref = 0);
            int wCenter(int size, int ref = 0);
            std::pair<int, int> getSizePixel();
    };
}

#endif /* !GAMEMODULE_HPP_ */
