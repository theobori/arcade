/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** input
*/

#ifndef __INPUT__HPP__
    #define __INPUT__HPP__

    #include <string>

    #include "Button.hpp"

namespace Games {
    class Input : public Button {
        public:
            Input(Arcade::Sprites_t sprite);
            ~Input();
            std::string getFormattedData();
            void addString(std::string str);
            void removeString(size_t cout);

        private:
            std::string _text;
    };
}

#endif /* !__INPUT__HPP__ */
