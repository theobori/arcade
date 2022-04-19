/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** oneClick
*/

#ifndef __LIBSELECTOR__HPP__
    #define __LIBSELECTOR__HPP__

    #include "Button.hpp"
    #include "../GameData.hpp"

namespace Games {

    class LibSelector : public Button {

        public:
            LibSelector(Arcade::Sprites_t sprite);
            ~LibSelector();

            Select<std::string> &getData();
            std::string getFormattedData();
            std::string getSelected();
            std::string getDetails();

        private:
            Select<std::string> _data;
    };
}

#endif /* !__LIBSELECTOR__HPP__ */

