/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** data
*/

#ifndef __GAMEDATA__HPP__
    #define __GAMEDATA__HPP__

    #include <iostream>
    #include <vector>

    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <fstream>
    #include <sstream>
    #include "../GamesErrors.hpp"

namespace Games {
    class GameSave {
        public:
            std::string username;
            size_t score;
    };

    class GameData {
        public:
            GameData(std::string path);
            GameData();
            ~GameData();

            void addGameSave(std::string username, unsigned int score);
            std::vector<GameSave> getGameSaves() const;
            GameSave getGameSave(std::size_t index) const;
            GameSave getHighScore() const;
            void updateSave();
            
            static std::vector<std::string> split(std::string data, std::string separator);
            static bool isDigits(const std::string& s);

        private:
            std::string _name;
            std::string _pathToSave;
            std::vector<GameSave> _saves;
    };
}

#endif /* !__GAMEDATA__HPP__ */
