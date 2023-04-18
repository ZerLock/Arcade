/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>

game::Menu::Menu() :
    _libs(),
    _games(),
    _spritesheets(),
    _username(),
    _selectedLib(0),
    _preselectedLib(0),
    _selectedGame(0),
    _preselectedGame(0),
    _deltaTime(std::chrono::duration<double>::zero()),
    _globalX(0)
{}

game::Menu::~Menu() {}

const std::vector<arcade::Spritesheet> &game::Menu::getSpritesheets() const
{
    return _spritesheets;
}

void game::Menu::compute(std::chrono::duration<double> &dtime, arcade::IContext &context)
{
    (void)context;

    _deltaTime += dtime;
    if (_deltaTime < FRAMERATE) {
        return;
    }

    _deltaTime = std::chrono::duration<double>::zero();
}

void game::Menu::handleInput(const arcade::KeyInput &key)
{
    switch (key.mapping) {
        case arcade::Keymaps::UP:
            if (_preselectedGame == 0) {
                _preselectedGame = _games.size();
            }
            _preselectedGame--;
            break;
        case arcade::Keymaps::DOWN:
            _preselectedGame = (_preselectedGame + 1) % _games.size();
            break;
        case arcade::Keymaps::LEFT:
            if (_preselectedLib == 0) {
                _preselectedLib = _libs.size();
            }
            _preselectedLib--;
            break;
        case arcade::Keymaps::RIGHT:
            _preselectedLib = (_preselectedLib + 1) % _libs.size();
            break;
        default:
            break;
    }
}

void game::Menu::render(arcade::IContext &context)
{
    context.clearWin();

    std::size_t index = 0;

    // Display menu title
    context.drawText({ "Arcade", WHITE, BLACK }, _globalX, 0);

    // Display welcome message with username
    context.drawText({ "Welcome back, " + _username + "!", WHITE, BLACK }, _globalX, 2);

    // Display game libraries
    std::size_t y = 4;
    context.drawText({ "Games:", WHITE, BLACK }, _globalX, y++);
    for (auto &it: _games) {
        char currentColor = index == _selectedGame ? RED : WHITE;

        context.drawText({ (index == _preselectedGame ? "> " : "") + it, currentColor, BLACK }, _globalX, y++);
        index++;
    }

    // Display graphic libraries
    index=0;
    y++;
    context.drawText({ "Graphicals:", WHITE, BLACK }, _globalX, y++);
    for (auto &it: _libs) {
        char currentColor = index == _selectedLib ? RED : WHITE;

        context.drawText({ (index == _preselectedLib ? "> " : "") + it, currentColor, BLACK }, _globalX, y++);
        index++;
    }

    // Display score
    y++;
    context.drawText({ "Scores:", WHITE, BLACK }, _globalX, y++);
    for (auto &it : _scores) {
        if (_games.at(_preselectedGame) == it.first) {
            std::sort(it.second.begin(), it.second.end(), _sortByScore); // Sort scores
            for (auto &player : it.second) {
                // sort socre
                context.drawText({ player.first + ": " + std::to_string(player.second) , WHITE, BLACK }, _globalX + 1, y++);
            }
        }
    }

    context.refreshWin();
}

bool game::Menu::_sortByScore(const std::pair<std::string, std::size_t> &a, const std::pair<std::string, std::size_t> &b)
{
    return (a.second > b.second);
}

void game::Menu::setScores(std::map<std::string, std::vector<std::pair<std::string, std::size_t>>> scores)
{
    _scores = scores;
}

void game::Menu::setLibraries(std::vector<std::string> libs, std::size_t selectedLib)
{
    _libs = libs;
    _selectedLib = selectedLib;
}

void game::Menu::setGames(std::vector<std::string> games)
{
    _games = games;
}

void game::Menu::setUsername(const std::string &username)
{
    _username = username;
}

std::size_t game::Menu::getSelectedGame() const
{
    return _preselectedGame;
}

std::size_t game::Menu::getSelectedLib() const
{
    return _preselectedLib;
}

void game::Menu::setSelectedGame(std::size_t index)
{
    _selectedGame = index;
    _preselectedGame = _selectedGame;
}

void game::Menu::setSelectedLib(std::size_t index)
{
    _selectedLib = index;
    _preselectedLib = _selectedLib;
}
