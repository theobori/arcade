/*
** EPITECH PROJECT, 2022
** Libs
** File description:
** Errors
*/

#ifndef __GRAPHICSERRORS_HPP__
    #define __GRAPHICSERRORS_HPP__

    #include <string>
    #include <exception>

namespace Libs {
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

    EXCEPTION_BASE(GraphicsError)
    NEW_EXCEPTION(SFMLError, GraphicsError)
    NEW_EXCEPTION(NcursesError, GraphicsError)
    NEW_EXCEPTION(SDLError, GraphicsError)
}

#endif /* !__GRAPHICSERRORS_HPP__ */
