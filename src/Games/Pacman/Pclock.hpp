/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include <ctime>
    #include <iostream>

class Pclock {
    public:
        Pclock(float refreshTime);
        ~Pclock();
        bool check();
        void reset();
        float getLeftTime();

    private:
        clock_t _clock;
        float _refreshTime;
};

#endif /* !CLOCK_HPP_ */
