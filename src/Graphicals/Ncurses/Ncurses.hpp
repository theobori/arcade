/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Ncurses
*/

#ifndef __NCURSES_HPP__
    #define __NCURSES_HPP__

    #include <memory>
    #include <iostream>
    #include <map>
    #include <ncurses.h>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>

    #include "../DisplayModule.hpp"
    #include "../GraphicsErrors.hpp"

namespace Libs {
    class Ncurses : public DisplayModule {

        public:
            Ncurses();
            ~Ncurses();

            std::vector<Arcade::KeyEvent_t> getEvents();
    
            void init(std::string name, int w, int h);
            void init_pair_color();
            int rbg_to_color(int r, int g, int b);

            void close();
            bool isOpen() const;
            void display() const;
            void my_clear() const;

            void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes,
                std::unordered_map<std::string, Arcade::Sprites_t> sprites,
                std::unordered_map<std::string, Arcade::Text_t> texts);

            bool drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            bool drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            bool drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);

            std::string my_get_file(std::string filename);
            std::vector<std::string> splitString(std::string str, std::string delimiter);
            void my_print(int y, int x, std::string filename, int ft, int bg);

            void setSizePixel(std::pair<int, int> size);
            void setSizeWindows(std::pair<int, int> size);

        private:
            std::map<int, Arcade::KeyState> _keyMap;
            std::map<int, std::vector<int>> color;
            std::map<std::string, std::string> _sprites;

            MEVENT _event;
            WINDOW *_window;

            float width;
            float height;
            bool _open;
            std::pair<int, int> _pixelSize;
    };
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create()
    {
        return (std::make_shared<Libs::Ncurses>());
    }
}

#endif /* !NCURSES_HPP_ */
