/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Context
*/

#include "Context.hpp"

arcade::Context::Context(core::Core &core)
    : _core(core)
{}

arcade::Context::~Context() {}

void arcade::Context::clearWin()
{
    _core.getRenderer()->clearWin();
}

void arcade::Context::refreshWin()
{
    _core.getRenderer()->refreshWin();
}

void arcade::Context::drawSprite(const arcade::SpriteCostume &sprite, double x, double y)
{
    _core.getRenderer()->drawSprite(sprite, x, y);
}

void arcade::Context::drawText(const arcade::TextDisplay &text, double x, double y)
{
    _core.getRenderer()->drawText(text, x, y);
}

void arcade::Context::saveScore(const std::size_t &score)
{
    _core.saveScore(score);
}
