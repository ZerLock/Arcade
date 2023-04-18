/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Pacman
*/

#include "../../include/games/Pacman.hpp"

std::vector<std::vector<char>> game::Pacman::initMap()
{
    std::ifstream ifs("./assets/pacman/pacman.map");
    std::string reader;
    std::vector<std::vector<char>> res;
    if (ifs.bad()) {
        exit(84);
    }
    while (std::getline(ifs, reader)) {
        std::vector<char> buffer(reader.begin(), reader.end());
        res.push_back(buffer);
    }
    return res;
}

Coords game::Pacman::findStart(Board board, char c)
{
    Coords coo = Coords();
    for (std::size_t i = 0; i < board.map.size(); i++) {
        if (std::count(board.map[i].begin(), board.map[i].end(), c) > 0) {
            coo.x = i;
            auto itr = std::find(board.map[i].begin(), board.map[i].end(), c);
            auto buffer = std::distance(board.map[i].begin(), itr);
            coo.y = buffer;
            break;
        }
    }
    return coo;
}

game::Pacman::Board game::Pacman::initBoard()
{
    Board board = Board();
    board.map = this->initMap();
    board.pacman = findStart(board, 'P');
    board.xmax = board.map.size();
    board.ymax = board.map[0].size();
    return board;
}

game::Pacman::Pacman()
{
    _sheets.push_back({
        0,
        "./assets/pacman/pacman_sheet.png",
        "./assets/pacman/pacman_sheet_ncurses.txt",
        {64, 64}
    });
    _board = initBoard();
    _redGhost = IAGhost(_board.map, '1');
    _blueGhost = IAGhost(_board.map, '2');
    _orangeGhost = IAGhost(_board.map, '3');
    _pinkGhost = IAGhost(_board.map, '4');
    _dir = RIGHT;
    _lastDir = NONE;
    _status = SUCCESS;
    _deltaTime = std::chrono::duration<double>::zero();
    _score = 0;
    _level = 4;
}

game::Pacman::~Pacman()
{
}

bool game::Pacman::winCondition() const
{
    for (std::size_t i = 0; i < _board.map.size(); i++) {
        if (std::count(_board.map[i].begin(), _board.map[i].end(), '.') > 0)
            return false;
    }
    return true;
}

bool game::Pacman::looseCondition(arcade::IContext &context)
{
    if (_redGhost.isColision(_board.pacman) == true) {
        context.saveScore(_score);
        _status = FAILURE;
        return true;
    }
    if (_blueGhost.isColision(_board.pacman) == true) {
        context.saveScore(_score);
        _status = FAILURE;
        return true;
    }
    if (_orangeGhost.isColision(_board.pacman) == true) {
        context.saveScore(_score);
        _status = FAILURE;
        return true;
    }
    if (_pinkGhost.isColision(_board.pacman) == true) {
        context.saveScore(_score);
        _status = FAILURE;
        return true;
    }
    return false;
}

const std::vector<arcade::Spritesheet> &game::Pacman::getSpritesheets() const
{
    return _sheets;
}

void game::Pacman::compute(std::chrono::duration<double> &dtime, arcade::IContext &context)
{
    _deltaTime += dtime;
    _deltaTimeGhost += dtime;
    if (_deltaTime >= FRAMERATE) {
        if (_status == SUCCESS) {
            _deltaTime = std::chrono::duration<double>::zero();
            move(context);
            if (winCondition() == true) {
                _board = initBoard();
                _dir = RIGHT;
                _deltaTime = std::chrono::duration<double>::zero();
                _status = SUCCESS;
                _redGhost = IAGhost(_board.map, '1');
                _blueGhost = IAGhost(_board.map, '2');
                _orangeGhost = IAGhost(_board.map, '3');
                _pinkGhost = IAGhost(_board.map, '4');
                _level += 1;
            }
        }
    }
    auto level = (_level == 1) ? LEVELONE : (_level == 2) ? LEVELTWO : (_level == 3) ? LEVELTHREE : LEVELFOUR;
    if (_deltaTimeGhost >= level) {
        if (_status == SUCCESS) {
            _redGhost.modifyDir(_board.map, _board.pacman, _board.xmax, _board.ymax);
            _blueGhost.modifyDir(_board.map, _board.pacman, _board.xmax, _board.ymax);
            _orangeGhost.modifyDir(_board.map, _board.pacman, _board.xmax, _board.ymax);
            _pinkGhost.modifyDir(_board.map, _board.pacman, _board.xmax, _board.ymax);
            moveAllGhosts(context);
            _deltaTimeGhost = std::chrono::duration<double>::zero();
        }
    }
}

void game::Pacman::move(arcade::IContext &context)
{
    Coords buffer = Coords();
    buffer.x = _board.pacman.x;
    buffer.y = _board.pacman.y;
    if (_lastDir == game::Pacman::Direction::UP) {
        if (_board.pacman.x != 0) {
            if (_board.map[_board.pacman.x - 1][_board.pacman.y] != '#') {
                _dir = UP;
                _lastDir = NONE;
            }
        }
    } else if (_lastDir == game::Pacman::Direction::DOWN) {
        if (_board.pacman.x != _board.xmax) {
            if (_board.map[_board.pacman.x + 1][_board.pacman.y] != '#') {
                _dir = DOWN;
                _lastDir = NONE;
            }
        }
    } else if (_lastDir == game::Pacman::Direction::LEFT) {
        if (_board.pacman.y != 0) {
            if (_board.map[_board.pacman.x][_board.pacman.y - 1] != '#') {
                _dir = LEFT;
                _lastDir = NONE;
            }
        }
    } else if (_lastDir == game::Pacman::Direction::RIGHT) {
        if (_board.pacman.y != _board.ymax) {
            if (_board.map[_board.pacman.x][_board.pacman.y + 1] != '#') {
                _dir = RIGHT;
                _lastDir = NONE;
            }
        }
    }
    if (_dir == game::Pacman::Direction::UP) {
        if (_board.pacman.x != 0) {
            if (_board.map[_board.pacman.x - 1][_board.pacman.y] != '#') {
                _board.pacman.x -= 1;
            }
        }
    } else if (_dir == game::Pacman::Direction::DOWN) {
        if (_board.pacman.x != _board.xmax) {
            if (_board.map[_board.pacman.x + 1][_board.pacman.y] != '#') {
                _board.pacman.x += 1;
            }
        }
    } else if (_dir == game::Pacman::Direction::LEFT) {
        if (_board.pacman.y != 0) {
            if (_board.map[_board.pacman.x][_board.pacman.y - 1] != '#') {
                _board.pacman.y -= 1;
            }
        }
    } else if (_dir == game::Pacman::Direction::RIGHT) {
        if (_board.pacman.y != _board.ymax) {
            if (_board.map[_board.pacman.x][_board.pacman.y + 1] != '#') {
                _board.pacman.y += 1;
            }
        }
    }
    if (buffer.x != _board.pacman.x || buffer.y != _board.pacman.y) {
        if (_board.map[_board.pacman.x][_board.pacman.y] == 'L') {
            _board.pacman.x = 14;
            _board.pacman.y = 25;
            _dir = LEFT;
        } else if (_board.map[_board.pacman.x][_board.pacman.y] == 'R') {
            _board.pacman.x = 14;
            _board.pacman.y = 2;
            _dir = RIGHT;
        } else if (_board.map[_board.pacman.x][_board.pacman.y] == '.') {
            _score += 1;
        }
        if (looseCondition(context) == true) {
            _board = initBoard();
            _dir = RIGHT;
            _lastDir = NONE;
            _deltaTime = std::chrono::duration<double>::zero();
            _redGhost = IAGhost(_board.map, '1');
            _blueGhost = IAGhost(_board.map, '2');
            _orangeGhost = IAGhost(_board.map, '3');
            _pinkGhost = IAGhost(_board.map, '4');
        } else {
            _board.map[_board.pacman.x][_board.pacman.y] = 'P';
            _board.map[buffer.x][buffer.y] = ' ';
        }
    }
}

void game::Pacman::moveAllGhosts(arcade::IContext &context)
{
    Coords buffer = _redGhost.getCoords();
    _redGhost.moveGhost(_board.map);
    if (looseCondition(context) == true) {
            _board = initBoard();
            _dir = RIGHT;
            _lastDir = NONE;
            _deltaTime = std::chrono::duration<double>::zero();
            _redGhost = IAGhost(_board.map, '1');
            _blueGhost = IAGhost(_board.map, '2');
            _orangeGhost = IAGhost(_board.map, '3');
            _pinkGhost = IAGhost(_board.map, '4');
    }
    _redGhost.setWalked(_board.map[_redGhost.getCoords().x][_redGhost.getCoords().y]);
    _board.map[_redGhost.getCoords().x][_redGhost.getCoords().y] = '1';
    if (buffer.x != _redGhost.getCoords().x || buffer.y != _redGhost.getCoords().y)
        _board.map[buffer.x][buffer.y] = _redGhost.getWalked();
    buffer = _blueGhost.getCoords();
    _blueGhost.moveGhost(_board.map);
    if (looseCondition(context) == true) {
            _board = initBoard();
            _dir = RIGHT;
            _lastDir = NONE;
            _deltaTime = std::chrono::duration<double>::zero();
            _redGhost = IAGhost(_board.map, '1');
            _blueGhost = IAGhost(_board.map, '2');
            _orangeGhost = IAGhost(_board.map, '3');
            _pinkGhost = IAGhost(_board.map, '4');
    }
    _blueGhost.setWalked(_board.map[_blueGhost.getCoords().x][_blueGhost.getCoords().y]);
    _board.map[_blueGhost.getCoords().x][_blueGhost.getCoords().y] = '2';
    if (buffer.x != _blueGhost.getCoords().x || buffer.y != _blueGhost.getCoords().y)
        _board.map[buffer.x][buffer.y] = _blueGhost.getWalked();
    buffer = _orangeGhost.getCoords();
    _orangeGhost.moveGhost(_board.map);
    if (looseCondition(context) == true) {
            _board = initBoard();
            _dir = RIGHT;
            _lastDir = NONE;
            _deltaTime = std::chrono::duration<double>::zero();
            _redGhost = IAGhost(_board.map, '1');
            _blueGhost = IAGhost(_board.map, '2');
            _orangeGhost = IAGhost(_board.map, '3');
            _pinkGhost = IAGhost(_board.map, '4');
    }
    _orangeGhost.setWalked(_board.map[_orangeGhost.getCoords().x][_orangeGhost.getCoords().y]);
    _board.map[_orangeGhost.getCoords().x][_orangeGhost.getCoords().y] = '3';
    if (buffer.x != _orangeGhost.getCoords().x || buffer.y != _orangeGhost.getCoords().y)
        _board.map[buffer.x][buffer.y] = _orangeGhost.getWalked();
    buffer = _pinkGhost.getCoords();
    _pinkGhost.moveGhost(_board.map);
    if (looseCondition(context) == true) {
            _board = initBoard();
            _dir = RIGHT;
            _lastDir = NONE;
            _deltaTime = std::chrono::duration<double>::zero();
            _redGhost = IAGhost(_board.map, '1');
            _blueGhost = IAGhost(_board.map, '2');
            _orangeGhost = IAGhost(_board.map, '3');
            _pinkGhost = IAGhost(_board.map, '4');
    }
    _pinkGhost.setWalked(_board.map[_pinkGhost.getCoords().x][_pinkGhost.getCoords().y]);
    _board.map[_pinkGhost.getCoords().x][_pinkGhost.getCoords().y] = '4';
    if (buffer.x != _pinkGhost.getCoords().x || buffer.y != _pinkGhost.getCoords().y)
        _board.map[buffer.x][buffer.y] = _pinkGhost.getWalked();
}

void game::Pacman::handleInput(const arcade::KeyInput &key)
{
    // Put all of the input
    if (key.mapping == arcade::Keymaps::UP) {
        _lastDir = UP;
        if (_board.pacman.x != 0) {
            if (_board.map[_board.pacman.x - 1][_board.pacman.y] != '#') {
                _dir = UP;
            }
        }
    }
    if (key.mapping == arcade::Keymaps::DOWN) {
        _lastDir = DOWN;
        if (_board.pacman.x != _board.xmax) {
            if (_board.map[_board.pacman.x + 1][_board.pacman.y] != '#') {
                _dir = DOWN;
            }
        }
    }
    if (key.mapping == arcade::Keymaps::LEFT) {
        _lastDir = LEFT;
        if (_board.pacman.y != 0) {
            if (_board.map[_board.pacman.x][_board.pacman.y - 1] != '#') {
                _dir = LEFT;
            }
        }
    }
    if (key.mapping == arcade::Keymaps::RIGHT) {
        _lastDir = RIGHT;
        if (_board.pacman.y != _board.ymax) {
            if (_board.map[_board.pacman.x][_board.pacman.y + 1] != '#') {
                _dir = RIGHT;
            }
        }
    }
    if (key.mapping == arcade::PAUSE) {
        _status = _status == PAUSE ? SUCCESS : PAUSE;
    }
    if (key.mapping == arcade::RESTART && _status == FAILURE) {
        _status = SUCCESS;
        _board = initBoard();
        _dir = RIGHT;
        _lastDir = NONE;
        _deltaTime = std::chrono::duration<double>::zero();
        _score = 0;
        _level = 1;
        _redGhost = IAGhost(_board.map, '1');
        _blueGhost = IAGhost(_board.map, '2');
        _orangeGhost = IAGhost(_board.map, '3');
        _pinkGhost = IAGhost(_board.map, '4');
    }
    if (key.mapping == arcade::QUIT) {
        // Go back to the menu
    }
}

void game::Pacman::render(arcade::IContext &context)
{
    context.clearWin();
    if (_status == FAILURE) {
        context.drawText({ "YOU LOSE", RED, BLACK }, 22, 20);
        context.drawText({ "You scored " + std::to_string(_score) + " points", WHITE, BLACK }, 20, 21);
        context.drawText({ "Failed at level " + std::to_string(_level), WHITE, BLACK }, 20, 22);
        context.drawText({ "Press R to restart", WHITE, BLACK }, 20, 24);
    } else if (_status == SUCCESS || _status == PAUSE) {
        for (std::size_t i = 0; i < _board.map.size(); i++) {
            for (std::size_t j = 0; j < _board.map[i].size(); j++) {
                arcade::SpriteCostume costume;
                if (_board.map[i][j] == '#') {
                    costume = {0, {0, 3}};
                } else if (_board.map[i][j] == 'P') {
                    if (_dir == game::Pacman::Direction::UP)
                        costume = {0, {1, 1}};
                    else if (_dir == game::Pacman::Direction::DOWN)
                        costume = {0, {1, 0}};
                    else if (_dir == game::Pacman::Direction::LEFT)
                        costume = {0, {0, 1}};
                    else if (_dir == game::Pacman::Direction::RIGHT)
                        costume = {0, {0, 0}};
                } else if (_board.map[i][j] == '.') {
                    costume = {0, {1, 2}};
                } else if (_board.map[i][j] == 'L') {
                    costume = {0, {2, 2}};
                } else if (_board.map[i][j] == 'R') {
                    costume = {0, {3, 2}};
                } else if (_board.map[i][j] == '1') {
                    costume = {0, {2, 0}};
                } else if (_board.map[i][j] == '*') {
                    costume = {0, {0, 2}};
                } else if (_board.map[i][j] == '1') {
                    costume = {0, {2, 0}};
                } else if (_board.map[i][j] == '2') {
                    costume = {0, {2, 1}};
                } else if (_board.map[i][j] == '3') {
                    costume = {0, {3, 0}};
                } else if (_board.map[i][j] == '4') {
                    costume = {0, {3, 1}};
                } else
                    continue;
                context.drawSprite(costume, j, i);
            }
        }
        context.drawText({ "Score: " + std::to_string(_score), WHITE, BLACK }, 0, _board.map.size() + 1);
        if (_status == PAUSE) {
            context.drawText({ "PAUSE", WHITE, BLACK }, 0, _board.map.size() - 1);
        }
    }
    context.refreshWin();
}

Coords game::Pacman::IAGhost::findGhost(std::vector<std::vector<char>> map, char c) const
{
    Coords coo = Coords();
    for (std::size_t i = 0; i < map.size(); i++) {
        if (std::count(map[i].begin(), map[i].end(), c) > 0) {
            coo.x = i;
            auto itr = std::find(map[i].begin(), map[i].end(), c);
            auto buffer = std::distance(map[i].begin(), itr);
            coo.y = buffer;
            break;
        }
    }
    return coo;
}

game::Pacman::IAGhost::IAGhost(std::vector<std::vector<char>> map, char nb)
{
    _dir = NONE;
    _isColision = false;
    _pos = findGhost(map, nb);
    _walked = ' ';
}

game::Pacman::IAGhost::~IAGhost()
{}

char game::Pacman::IAGhost::getWalked() const
{
    return _walked;
}

void game::Pacman::IAGhost::setWalked(char c)
{
    _walked = c;
}

Coords game::Pacman::IAGhost::getCoords() const
{
    return _pos;
}

game::Pacman::Direction game::Pacman::IAGhost::getDir() const
{
    return _dir;
}

void game::Pacman::IAGhost::moveGhost(std::vector<std::vector<char>> map)
{
    if (_dir == UP) {
        if (map[_pos.x - 1][_pos.y] != '#' && map[_pos.x - 1][_pos.y] != '1' && map[_pos.x - 1][_pos.y] != '2' && map[_pos.x - 1][_pos.y] != '3' && map[_pos.x - 1][_pos.y] != '4') {
            _pos.x -=1;
        }
    }
    if (_dir == DOWN) {
        if (map[_pos.x + 1][_pos.y] != '#' && map[_pos.x + 1][_pos.y] != '1' && map[_pos.x + 1][_pos.y] != '2' && map[_pos.x + 1][_pos.y] != '3' && map[_pos.x + 1][_pos.y] != '4') {
            _pos.x +=1;
        }
    }
    if (_dir == LEFT) {
        if (map[_pos.x][_pos.y - 1] != '#' && map[_pos.x][_pos.y - 1] != '1' && map[_pos.x][_pos.y - 1] != '2' && map[_pos.x][_pos.y - 1] != '3' && map[_pos.x][_pos.y - 1] != '4') {
            _pos.y -=1;
        }
    }
    if (_dir == RIGHT) {
        if (map[_pos.x][_pos.y + 1] != '#' && map[_pos.x][_pos.y + 1] != '1' && map[_pos.x][_pos.y + 1] != '2' && map[_pos.x][_pos.y + 1] != '3' && map[_pos.x][_pos.y + 1] != '4') {
            _pos.y +=1;
        }
    }
}

bool game::Pacman::IAGhost::isColision(Coords pacman) const
{
    if (_pos.x == pacman.x && _pos.y == pacman.y)
        return true;
    return false;
}

void game::Pacman::IAGhost::modifyDir(std::vector<std::vector<char>> map, Coords pacman, std::size_t xmax, std::size_t ymax)
{
    if (_pos.x > pacman.x) {
        if (_pos.x != 0) {
            if (map[_pos.x - 1][_pos.y] != '#') {
                _dir = UP;
                return;
            }
        }
    }
    if (_pos.x < pacman.x) {
        if (_pos.x != xmax) {
            if (map[_pos.x + 1][_pos.y] != '#') {
                _dir = DOWN;
                return;
            }
        }
    }
    if (_pos.y > pacman.y) {
        if (_pos.y != 0) {
            if (map[_pos.x][_pos.y - 1] != '#') {
                _dir = LEFT;
                return;
            }
        }
    }
    if (_pos.y < pacman.y) {
        if (_pos.y != ymax) {
            if (map[_pos.x][_pos.y + 1] != '#') {
                _dir = RIGHT;
                return;
            }
        }
    }
    if (_pos.x != 0) {
        if (map[_pos.x - 1][_pos.y] != '#') {
            _dir = UP;
            return;
        }
    }
    if (_pos.y != 0) {
        if (map[_pos.x][_pos.y - 1] != '#') {
            _dir = LEFT;
            return;
        }
    }
    if (_pos.y != ymax) {
        if (map[_pos.x][_pos.y + 1] != '#') {
            _dir = RIGHT;
            return;
        }
    }
    if (_pos.x != xmax) {
        if (map[_pos.x + 1][_pos.y] != '#') {
            _dir = DOWN;
            return;
        }
    }
}

extern "C" {
    game::Pacman *entryPoint()
    {
        return new game::Pacman;
    }

    arcade::LibType getType()
    {
        return arcade::LibType::GAME;
    }

    std::string getName()
    {
        return "Pacman";
    }
}
