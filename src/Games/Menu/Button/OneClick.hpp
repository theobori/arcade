/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** oneClick
*/

#ifndef __ONECLICK__HPP__
    #define __ONECLICK__HPP__

    #include "Button.hpp"

namespace Games {
    class OneClick : public Button {
        public:
            OneClick(Arcade::Sprites_t sprite);
            ~OneClick();
    };
}

#endif /* !__ONECLICK__HPP__ */
