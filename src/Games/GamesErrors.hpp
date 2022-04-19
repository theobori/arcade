/*
** EPITECH PROJECT, 2022
** Libs
** File description:
** Errors
*/

#ifndef __GAMESERRORS_HPP__
    #define __GAMESERRORS_HPP__

    #include <string>
    #include <exception>

namespace Games {
    #define EXCEPTION_BASE(name) \
    class name: public std::exception \
    { \
        public: \
            name(std::string const &message, std::string const &component = "Unknown") noexcept; \
            const std::string &getComponent() const; \
            const char *what() const noexcept override; \
        private: \
            std::string _message; \
            std::string _componentName; \
    };\

    #define NEW_EXCEPTION(name, parent) \
    class name: public parent \
    { \
        public: \
            name(std::string const &message, std::string const &component) : parent(message, component) \
            {} \
    };

    EXCEPTION_BASE(GamesError)
    NEW_EXCEPTION(MenuError, GamesError)
    NEW_EXCEPTION(PacmanError, GamesError)
    NEW_EXCEPTION(NibblerError, GamesError)
    NEW_EXCEPTION(DlSelector, GamesError)
}

#endif /* !__GAMESERRORS_HPP__ */
