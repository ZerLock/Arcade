/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

#define FONT_SIZE   18

#define BLACK       0
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7

#include "Global.hpp"
#include <cstddef>
#include <string>

namespace arcade {

    /**
     * @brief Spritesheet used to create the spritesheet in the current graphical library
     *
     */
    struct Spritesheet {
        std::size_t id;
        std::string graphicPath;
        std::string textPath;
        Position unitDims;
    };

    /**
     * @brief SpriteCostume used to tell the graphical library what display in each sprite in each spritesheet
     *
     */
    struct SpriteCostume {
        std::size_t spritesheet;
        Position pos;
    };

    /**
     * @brief TextDisplay used to display text in current graphical library
     *
     */
    struct TextDisplay {
        std::string content;
        char fg;
        char bg;
    };
}

/**
 * @brief Overloaded operator to compare two SpriteCostume
 *
 * @param model
 * @param costume
 * @return true
 * @return false
 */
inline bool operator==(const arcade::SpriteCostume &model, const arcade::SpriteCostume &costume)
{
    return (model.spritesheet == costume.spritesheet && model.pos == costume.pos);
}

#endif /* !RENDER_HPP_ */
