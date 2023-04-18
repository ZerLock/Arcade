/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Ncurses
*/

#include "Ncurses.hpp"
#include <iostream>
#include <fstream>

render::Ncurses::Ncurses()
    : _mapping(), _spritesVector()
{
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    raw();
    start_color();

    _mapping = {
        {'a', arcade::RawKey::K_A},
        {'b', arcade::RawKey::K_B},
        {'c', arcade::RawKey::K_C},
        {'d', arcade::RawKey::K_D},
        {'e', arcade::RawKey::K_E},
        {'f', arcade::RawKey::K_F},
        {'g', arcade::RawKey::K_G},
        {'h', arcade::RawKey::K_H},
        {'i', arcade::RawKey::K_I},
        {'j', arcade::RawKey::K_J},
        {'k', arcade::RawKey::K_K},
        {'l', arcade::RawKey::K_L},
        {'m', arcade::RawKey::K_M},
        {'n', arcade::RawKey::K_N},
        {'o', arcade::RawKey::K_O},
        {'p', arcade::RawKey::K_P},
        {'q', arcade::RawKey::K_Q},
        {'r', arcade::RawKey::K_R},
        {'s', arcade::RawKey::K_S},
        {'t', arcade::RawKey::K_T},
        {'u', arcade::RawKey::K_U},
        {'v', arcade::RawKey::K_V},
        {'w', arcade::RawKey::K_W},
        {'x', arcade::RawKey::K_X},
        {'y', arcade::RawKey::K_Y},
        {'z', arcade::RawKey::K_Z},
        {N_SPACE, arcade::RawKey::K_SPACE},
        {N_ESCAPE, arcade::RawKey::K_ESCAPE},
        {N_ENTER, arcade::RawKey::K_ENTER},
        {N_BACKSPACE, arcade::RawKey::K_BACKSPACE},
        {N_UP, arcade::RawKey::K_UP},
        {N_DOWN, arcade::RawKey::K_DOWN},
        {N_LEFT, arcade::RawKey::K_LEFT},
        {N_RIGHT, arcade::RawKey::K_RIGHT},
    };
}

render::Ncurses::~Ncurses()
{
    endwin();
}

void render::Ncurses::loadSpritesheets(const std::vector<arcade::Spritesheet> &spritesheets)
{
    _spritesVector.clear();
    int index = 0;
    for (const auto& spritesheet : spritesheets) {
        std::ifstream file(spritesheet.textPath);
        std::string line;
        NSprite tmp;
        Position pos = {0, 0};
        while (std::getline(file, line)) {
            for (size_t i = 0; i < line.size(); i += 4) {
                tmp.foreground = std::stoi(line.substr(i, 1));
                tmp.background = std::stoi(line.substr(i + 1, 1));
                tmp.sprite = line.substr(i + 2, 2);
                pos.x = i / 4;
                init_pair(index, tmp.foreground, tmp.background);
                tmp.color_pair = index;
                tmp.spritesheetIdx = spritesheet.id;
                _spritesVector.emplace_back(pos, tmp);
                index++;
            }
            pos.y++;
        }
    }
}

std::vector<arcade::Event> render::Ncurses::pollEvents()
{
    std::vector<arcade::Event> inputs;

    auto tmp = getch();
    if (tmp != ERR) {
        if (auto key = _mapping.find(tmp); key != _mapping.end()) {
            inputs.push_back({ (*key).second, {0, 0} });
        }
    }
    return inputs;
}

void render::Ncurses::clearWin()
{
    erase();
}

void render::Ncurses::refreshWin()
{
    refresh();
}

void render::Ncurses::drawSprite(const arcade::SpriteCostume &sprite, double x, double y)
{
    for (auto &it : _spritesVector) {
        if (it.first == sprite.pos && sprite.spritesheet == it.second.spritesheetIdx) { // Use overloaded operator== to compare two Coords structs
            attron(COLOR_PAIR(it.second.color_pair));
            mvprintw(y, x * 2, it.second.sprite.c_str());
            attroff(COLOR_PAIR(it.second.color_pair));
        }
    }
}

void render::Ncurses::drawText(const arcade::TextDisplay &text, double x, double y)
{
    mvprintw(y, x * 2, text.content.c_str());
}

extern "C" {
    render::Ncurses *entryPoint()
    {
        return new render::Ncurses;
    }

    arcade::LibType getType()
    {
        return arcade::LibType::GRAPHICAL;
    }

    std::string getName()
    {
        return "Ncurses";
    }
}
