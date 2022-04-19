/*
** EPITECH PROJECT, 2022
** Libs
** File description:
** Errors
*/

#include "GraphicsErrors.hpp"

Libs::GraphicsError::GraphicsError(std::string const &message, std::string const &component) noexcept : _message(message), _componentName(component)
{
}

const char *Libs::GraphicsError::what() const noexcept 
{
    return (this->_message.data());
}

const std::string &Libs::GraphicsError::getComponent() const
{
    return (this->_componentName);
}
