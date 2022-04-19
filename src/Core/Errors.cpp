/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Errors
*/

#include "Errors.hpp"

Arcade::CoreError::CoreError(std::string const &message, std::string const &component) noexcept : _message(message), _componentName(component)
{
}

const char *Arcade::CoreError::what() const noexcept 
{
    return (this->_message.data());
}

const std::string &Arcade::CoreError::getComponent() const
{
    return (this->_componentName);
}
