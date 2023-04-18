/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

core::DLLoader::DLLoader(const std::string &path, int mode) :
    _path(path), _handle(dlopen(path.c_str(), mode), dlclose)
{
    if (!_handle.get())
    {
        std::cout << "Cannot open the library:" << std::endl;
        std::cout << "\t" << dlerror() << std::endl;
        exit(84);
    }
}

std::string core::DLLoader::getPath() const
{
    return _path;
}
