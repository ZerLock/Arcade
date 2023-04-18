/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Error
*/

#include "Error.hpp"

core::Error::Error(const std::string &msg)
    : _msg(msg)
{}

core::Error::~Error() {}

const char *core::Error::what() const noexcept
{
    return _msg.c_str();
}
