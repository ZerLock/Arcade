/*
** EPITECH PROJECT, 2023
** cpp-epitech-template
** File description:
** main
*/

#include "Core.hpp"
#include "DLLoader.hpp"
#include "IRenderer.hpp"
#include "IGame.hpp"
#include "Pacman.hpp"

std::string getUsage()
{
    std::string content;
    std::fstream ifs("./assets/usage.txt", std::fstream::in);

    if (ifs.is_open()) {
        std::getline(ifs, content, '\0');
        ifs.close();
    }
    return content;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << getUsage() << std::endl;
        return 84;
    }

    try {
        core::Core core = core::Core(std::string(av[1]));
        core.coreLoop();
    } catch (const core::Error &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
