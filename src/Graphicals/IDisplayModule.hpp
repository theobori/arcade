/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** IDisplayModule
*/

#ifndef __IDISPLAYMODULE_HPP__
    #define __IDISPLAYMODULE_HPP__

    #include <iostream>
    #include <vector>
    #include <unordered_map>

    #include "../Core/Interoperability.hpp"

namespace Libs {

    class IDisplayModule {

        public:
            virtual ~IDisplayModule() = default;
            virtual void init(std::string name = "Unknown", int w = 800, int h = 600) = 0;
            virtual bool isOpen() const = 0;
            virtual void close() = 0;
            virtual void my_clear() const = 0;
            virtual void setBackgroundColor(int, int, int) = 0;
            virtual void display() const = 0;
            virtual void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes,
                std::unordered_map<std::string, Arcade::Sprites_t> sprites,
                std::unordered_map<std::string, Arcade::Text_t> texts) = 0;
            virtual std::vector<Arcade::KeyEvent_t> getEvents() = 0;
            virtual void setSizePixel(std::pair<int, int> size) = 0;
            virtual void setSizeWindows(std::pair<int, int> size) = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */
