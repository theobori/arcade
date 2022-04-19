/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** button
*/

#ifndef __IBUTTON_HPP__
    #define __IBUTTON_HPP__

    #include <iostream>

    #include "../../Select.hpp"
    #include "../../../Core/Interoperability.hpp"
    #include "../GameData.hpp"

namespace Games {

    class IButton {

        public:

            enum TYPE {
                DEFAULT,
                ONE_CLICK,
                LIB_SELECTOR,
                GAME_SELECTOR,
                INPUT,
                PLAY
            };

            virtual ~IButton() = default;

            virtual TYPE getType() const = 0;
            virtual Arcade::Sprites_t getSprite() const = 0;
            virtual std::string getFormattedData() = 0;
            virtual void addString(std::string str) = 0;
            virtual void removeString(size_t count) = 0;
            virtual void refreshSelector() = 0;

            virtual std::string getSelected() = 0;
            virtual std::string getDetails() = 0;
            virtual std::string getBest() = 0;
    };
}

#endif /* !__BUTTON_HPP__ */
