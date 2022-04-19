/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Apple
*/

#ifndef APPLE_HPP_
    #define APPLE_HPP_

    #include "../GameModule.hpp"

namespace Games {
    class Apple {
        public:
            Apple(int x, int y);
            ~Apple();

            Arcade::Sprites_t getApple();
        protected:
            Arcade::Sprites_t _apple;
        private:
    };
}

#endif /* !APPLE_HPP_ */
