/*
** EPITECH PROJECT, 2022
** Libs
** File description:
** Errors
*/

#include "GamesErrors.hpp"

Games::GamesError::GamesError(std::string const &message, std::string const &component) noexcept : _message(message), _componentName(component)
{
}

const char *Games::GamesError::what() const noexcept 
{
    return (this->_message.data());
}

const std::string &Games::GamesError::getComponent() const
{
    return (this->_componentName);
}
