/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** DisplayModule
*/

#ifndef __DISPLAYMODULE_HPP__
    #define __DISPLAYMODULE_HPP__

    #include <iostream>
    #include "IDisplayModule.hpp"

namespace Libs {
    class DisplayModule: public IDisplayModule {
        public:
            DisplayModule();
            ~DisplayModule();
            void init(std::string name, int w, int h);
            void stop();
            void close();
            void my_clear() const;
            bool isOpen() const;
            void display() const;
            void setBackgroundColor(int, int, int);
            void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes,
                std::unordered_map<std::string, Arcade::Sprites_t> sprites,
                std::unordered_map<std::string, Arcade::Text_t> texts);
            std::vector<Arcade::KeyEvent_t> getEvents();
            void setSizePixel(std::pair<int, int> size);
            void clearAssets();
            void setSizeWindows(std::pair<int, int> size);
    };
}

#endif /* !DISPLAYMODULE_HPP_ */
