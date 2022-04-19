/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Body
*/

#ifndef BODY_HPP_
    #define BODY_HPP_

    #include <iostream>
    #include <cstdlib>
    #include <climits>
    #include "../GameModule.hpp"


namespace Games {
    class Body {
        public:
            Body(int x, int y, int dir);
            ~Body();
            void SetPos(int x, int y);
            Arcade::Sprites_t getBody();
            void walk(std::pair<int, int> pos);
            void walkCorner(int pervX, int pervY);
            int getX();
            int getY();

        private:
            Arcade::Sprites_t _body;
            int _num;
    };
}

#endif /* !BODY_HPP_ */
