/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** map
*/

#ifndef MAPS_HPP_
    #define MAPS_HPP_

    #include <iostream>
    #include <string>
    #include <map>
    #include <unordered_map>
    #include <fstream>
    #include <sstream>

    #include "../GameModule.hpp"

namespace Games {
    class Nibbler;

    class Maps {
        public:
            Maps();
            ~Maps();

            void loadMaps();
            std::string my_get_file(std::string filename);
            void displayMaps();
            std::unordered_map<std::string, Arcade::Rect_t> getMaps();

        private:
            std::string _maps;
            std::unordered_map<std::string, Arcade::Rect_t> _mapShape;
    };
}


#endif
