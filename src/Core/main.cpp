/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** main
*/

#include "../Games/GamesErrors.hpp"
#include "../Graphicals/GraphicsErrors.hpp"
#include "./Errors.hpp"

#include "DLLoader.hpp"
#include "Core.hpp"

int main(int ac, char **av) 
{

    if (ac != 2) {
        std::cerr << "Usage: ./arcade lib/graphical_library.so" << std::endl;
        return (84);
    }

    Arcade::Core core;
    try {
        core.init();
        core.initGraphics(std::string(av[1]));
        core.CoreLoop();
        return (0);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    return (0);
}
