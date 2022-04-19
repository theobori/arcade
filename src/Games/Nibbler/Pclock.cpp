/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Clock
*/

#include "Pclock.hpp"

Pclock::Pclock(float refreshTime)
{
    this->_refreshTime = refreshTime;
    this->_clock = clock();
}

Pclock::~Pclock()
{
}

bool Pclock::check()
{
	clock_t now = clock();
	float diff = now - this->_clock;

    if (diff / CLOCKS_PER_SEC > this->_refreshTime) {
        this->_clock = now;
        return (true);
    }
    return (false);
}

void Pclock::reset()
{
    this->_clock = clock();
}

float Pclock::getLeftTime()
{
    float diff = clock() - this->_clock;

    return(diff / CLOCKS_PER_SEC);
}