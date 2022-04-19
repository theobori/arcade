/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** oneClick
*/

#ifndef __GAMESELECTOR__HPP__
    #define __GAMESELECTOR__HPP__

    #include "Button.hpp"
    #include "../GameData.hpp"

namespace Games {

    class GameSelector : public Button {

        public:
            GameSelector(Arcade::Sprites_t sprite);
            ~GameSelector();

            Select<GameData> &getData();
            std::string getFormattedData();
            std::string getSelected();
            std::string getDetails();
            std::string getBest();
            void refreshSelector();

        private:
            Select<GameData> _data;
    };
}

#endif /* !__GAMESELECTOR__HPP__ */
