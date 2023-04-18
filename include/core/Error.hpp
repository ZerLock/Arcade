/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <string>
#include <exception>

namespace core {

    class Error: public std::exception {
        public:
            Error(const std::string &msg);
            ~Error();

            const char *what() const noexcept;

        protected:
        private:
            std::string _msg;
    };
}

#endif /* !ERROR_HPP_ */
