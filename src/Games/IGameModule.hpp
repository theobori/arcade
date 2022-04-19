/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** IGameModule
*/

#ifndef __IGAMEMODULE_H__
    #define __IGAMEMODULE_H__

    #include "../Graphicals/IDisplayModule.hpp"

namespace Games {
    class IGameModule {

        public:
            virtual ~IGameModule() = default;
            virtual std::unordered_map<std::string, Arcade::Rect_t> getShapes() = 0;
            virtual std::unordered_map<std::string, Arcade::Sprites_t> getSprites() = 0;
            virtual std::unordered_map<std::string, Arcade::Text_t> getTexts() = 0;
            virtual std::pair<int, int> getSizeWindow() = 0;
            virtual std::pair<int, int> getSizePixel() = 0;
            virtual void update() = 0;
            virtual void handleEvents(std::vector<Arcade::KeyEvent_t> event) = 0;
    };
}

#endif /* !IGAMEMODULE_H_ */
