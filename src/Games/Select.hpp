/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** select
*/

#ifndef __SELECT_HPP__
    #define __SELECT_HPP__

    #include <iostream>
    #include <vector>
    #include <utility>

    #include "GamesErrors.hpp"

namespace Games {
    template <typename T>
    class Select {

        public:
            Select()
            {
                this->_index = 0;
            };

            ~Select()
            {

            };

            std::pair<std::string, T> &getCurrent()
            {
                if (this->_index < 0 || this->_index >= this->_arr.size())
                    throw (DlSelector("getCurrent Out of range", "Invalid index"));
                return (this->_arr.at(this->_index));
            }

            void addElement(std::string name, T ptr)
            {
                std::pair<std::string, T> element(name, ptr);
    
                this->_arr.push_back(element);
            }

            std::size_t getIndex() const
            {
                return (this->_index);
            }

            void previous()
            {
                if (this->_index <= 0)
                    this->_index = this->_arr.size() - 1;
                else
                    --this->_index;
            }

            void next()
            {
                this->_index++;
                if (this->_index >= this->_arr.size())
                    this->_index = 0;
            }

            void setIndex(std::size_t index)
            {
                if (this->_index < 0 || this->_index >= this->_arr.size())
                    throw (DlSelector("setIndex Out of range", "Invalid index"));
                this->_index = index;
            }

            std::vector<std::pair<std::string, T>> &getArr()
            {
                return (this->_arr);
            }

            T getByKey(std::string key)
            {
                T ret;

                for (auto it : this->_arr) {
                    if (it.first == key)
                        return (it.second);
                }
                return (ret);
            }

        private:
            std::vector<std::pair<std::string, T>> _arr;
            std::size_t _index;
    };
};

#endif /* !__SELECT_HPP__ */
