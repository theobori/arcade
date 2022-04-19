/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Graphics available
*/

#ifndef __GRAPHICSAVAILABLE_HPP__
    #define __GRAPHICSAVAILABLE_HPP__

    #include "IAvailableModule.hpp"
    #include <fstream>

namespace Utils {

    class Graphics : public IAvailable {
        public:
            Graphics();
            ~Graphics();
            std::vector<std::pair<std::string, std::string>> getData() const;
            std::size_t getCount() const;
            void fill();

        private:
            const std::vector<std::pair<std::string, std::string>> _available;
            std::vector<std::pair<std::string, std::string>> _ret;
    };
}
#endif /* !__GraphicsAVAILABLE_HPP__ */
