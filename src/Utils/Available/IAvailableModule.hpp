/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Available constants data
*/

#ifndef __AVAILABLE_HPP__
    #define __AVAILABLE_HPP__

    #include <iostream>
    #include <vector>

namespace Utils {
    class IAvailable {
        public:
            virtual ~IAvailable() = default;
            virtual void fill() = 0;
            virtual std::vector<std::pair<std::string, std::string>> getData() const = 0;
            virtual std::size_t getCount() const = 0;
    };
}

#endif /* !__AVAILABLE_HPP__ */
