/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Errors
*/

#ifndef __ERRORS_HPP__
    #define __ERRORS_HPP__

    #include <string>
    #include <exception>

namespace Arcade {
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
    };

    #define NEW_EXCEPTION(name, parent) \
    class name: public parent \
    { \
        public: \
            name(std::string const &message, std::string const &component) : parent(message, component) \
            {} \
    };

    EXCEPTION_BASE(CoreError)
    NEW_EXCEPTION(DLError, CoreError)
    NEW_EXCEPTION(DlSelector, CoreError)
}

#endif /* !ERRORS_HPP */
