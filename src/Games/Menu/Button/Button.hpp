/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** button
*/

#ifndef __BUTTON_HPP__
    #define __BUTTON_HPP__

    #include <iostream>

    #include "./IButton.hpp"
    #include "../../../Core/Interoperability.hpp"
    #include "../GameData.hpp"

namespace Games {

    class Button: public IButton {

        public:
            Button(TYPE type = TYPE::DEFAULT, Arcade::Sprites_t sprite = {});
            ~Button();

            TYPE getType() const;
            Arcade::Sprites_t getSprite() const;

            std::string getFormattedData();
            void addString(std::string str);
            void removeString(size_t count);
            std::string getSelected();
            std::string getDetails();
            std::string getBest();
            void refreshSelector();

        private:
            TYPE _type;
            Arcade::Sprites_t _sprite;
    };
}

#endif /* !__BUTTON_HPP__ */
