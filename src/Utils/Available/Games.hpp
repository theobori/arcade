/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Games available
*/

#ifndef __GAMESAVAILABLE_HPP__
    #define __GAMESAVAILABLE_HPP__

    #include "IAvailableModule.hpp"
    #include <fstream>

namespace Utils {

    class Games : public IAvailable {
        public:
            Games();
            ~Games();
            std::vector<std::pair<std::string, std::string>> getData() const;
            std::size_t getCount() const;
            void fill();

        private:
            const std::vector<std::pair<std::string, std::string>> _available;
            std::vector<std::pair<std::string, std::string>> _ret;
    };
}
#endif /* !__GAMESAVAILABLE_HPP__ */
