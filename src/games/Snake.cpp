/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Snake
*/

#include "Snake.hpp"

#include <utility>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

bool game::Snake::remove_from_list(Cells* elt, std::vector<Cells*>& vec)
{
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (is_same_place(*it, elt)) {
            delete *it;
            vec.erase(it);
            return true;
        }
    }
    return false;
}

enum game::Snake::Status game::Snake::move_snake(Board* board, enum Direction dir)
{
    Cells* beginning = get_next_move(board, dir);
    if (!beginning)
        return FAILURE;

    if (is_same_place(beginning, board->snake[1])) {
        delete beginning;
        return SUCCESS;
    }

    if (list_contains(beginning, board->snake)) {
        delete beginning;
        return FAILURE;
    }

    if (list_contains(beginning, board->foods)) {
        remove_from_list(beginning, board->foods);
        add_food(board);
    } else {
        board->snake.pop_back();
    }

    board->snake.insert(board->snake.begin(), beginning);
    _lastDir = dir;

    return SUCCESS;
}


bool game::Snake::is_same_place(Cells* cell1, Cells* cell2)
{
    return cell1->x == cell2->x && cell1->y == cell2->y;
}

game::Snake::Cells* game::Snake::get_next_move(Board* board, enum Direction dir)
{
    std::vector<game::Snake::Cells*> snake = board->snake;
    int new_x = snake.front()->x;
    int new_y = snake.front()->y;

    if (dir == UP)
        new_y--;
    else if (dir == DOWN)
        new_y++;
    else if (dir == LEFT)
        new_x--;
    else if (dir == RIGHT)
        new_x++;

    if (new_x < 1 || new_y < 1 || new_x >= board->xmax - 1 || new_y >= board->ymax - 1)
        return nullptr;

    return create_cell(new_x, new_y, dir);
}


game::Snake::Cells* game::Snake::create_cell_rand(int xmax, int ymax)
{
    return create_cell(rand() % xmax - 1, rand() % ymax - 1, UP);
}

void game::Snake::add_food(Board* board)
{
    Cells* new_food = nullptr;
    bool food_found = false;
    while (!food_found) {
        delete new_food;
        new_food = create_cell_rand(board->xmax, board->ymax);
        if (!list_contains(new_food, board->foods) && !list_contains(new_food, board->snake)) {
            food_found = true;
        }
    }
    board->foods.push_back(new_food);
}

bool game::Snake::list_contains(Cells* cell, const std::vector<game::Snake::Cells*>& vec)
{
    for (const auto& s : vec) {
        if (is_same_place(s, cell)) {
            return true;
        }
    }
    return false;
}

game::Snake::Cells* game::Snake::create_cell(int x, int y, enum Direction dir)
{
    auto* cell = new Cells;
    cell->x = x;
    cell->y = y;
    cell->dir = dir;
    return cell;
}

game::Snake::Board* game::Snake::create_board(std::vector<game::Snake::Cells *> snake, std::vector<game::Snake::Cells *> foods, int xmax, int ymax)
{
    auto* board = new Board;
    board->foods = std::move(foods);
    board->snake = std::move(snake);
    board->xmax = xmax;
    board->ymax = ymax;
    return board;
}

std::vector<game::Snake::Cells *> game::Snake::create_snake()
{
    std::vector<Cells *> snake;
    Cells* a = create_cell(25, 25, RIGHT);
    Cells* b = create_cell(24, 25, RIGHT);
    Cells* c = create_cell(23, 25, RIGHT);
    Cells* d = create_cell(22, 25, RIGHT);
    snake.emplace_back(a);
    snake.emplace_back(b);
    snake.emplace_back(c);
    snake.emplace_back(d);
    return snake;
}

void game::Snake::restart()
{
    _dir = RIGHT;
    _status = SUCCESS;
    _board = create_board(create_snake(), {}, 50, 50);
    for (int i = 0; i < 5; i++)
        add_food(_board);
}

game::Snake::Snake()
    : _sheets(), _board(), _deltaTime(), _dir(), _lastDir(), _status()
{
    _deltaTime = std::chrono::duration<double>::zero();
    _sheets.push_back({
        0,
        "./assets/snake/snake_sheet.png",
        "./assets/snake/snake_sheet_ncurses.txt",
        {64, 64}
    });

    _dir = RIGHT;
    _board = create_board(create_snake(), {}, 50, 50);
    for (int i = 0; i < 5; i++)
        add_food(_board);
}

game::Snake::~Snake() = default;

const std::vector<arcade::Spritesheet> &game::Snake::getSpritesheets() const
{
    return _sheets;
}

void game::Snake::compute(std::chrono::duration<double> &dtime, arcade::IContext &context)
{
    (void)context;
    _deltaTime += dtime;
    if (_deltaTime < FRAMERATE) {
        return;
    }

    if (_status != PAUSE && _status != FAILURE) {
        if (move_snake(_board, _dir) == FAILURE) {
            context.saveScore(_board->snake.size() - 4);
            _status = FAILURE;
        }
    }

    _deltaTime = std::chrono::duration<double>::zero();
}

void game::Snake::handleInput(const arcade::KeyInput &key)
{
    if (!key.mapping)
        return;
    if (key.mapping == arcade::Keymaps::UP && _lastDir != DOWN)
        _dir = UP;
    else if (key.mapping == arcade::Keymaps::DOWN && _lastDir != UP)
        _dir = DOWN;
    else if (key.mapping == arcade::Keymaps::LEFT && _lastDir != RIGHT)
        _dir = LEFT;
    else if (key.mapping == arcade::Keymaps::RIGHT && _lastDir != LEFT)
        _dir = RIGHT;
    else if (key.mapping == arcade::Keymaps::RESTART && _status == FAILURE)
        restart();
    else if (key.mapping == arcade::Keymaps::PAUSE)
        _status = _status == PAUSE ? SUCCESS : PAUSE;
}

void game::Snake::render(arcade::IContext &context)
{
    context.clearWin();

    std::vector<game::Snake::Cells *> tmp_snake = _board->snake;
    std::vector<game::Snake::Cells *> tmp_food = _board->foods;

    if (_status == FAILURE) {
        context.drawText({ "YOU LOSE", RED, BLACK }, 22, 20);
        context.drawText({ "You scored " + std::to_string(tmp_snake.size() - 4) + " points", WHITE, BLACK }, 20, 21);
        context.drawText({ "Press R to restart", WHITE, BLACK }, 20, 24);
    } else {
        for (std::vector<game::Snake::Cells *>::size_type i = 0; i < tmp_snake.size(); i++) {
            auto *s = tmp_snake[i];
            arcade::SpriteCostume costume = {};

            if (i == tmp_snake.size() - 1 && tmp_snake[i - 1]->dir == RIGHT)
                costume = {0, {4, 2}};
            if (i == tmp_snake.size() - 1 && tmp_snake[i - 1]->dir == LEFT)
                costume = {0, {3, 3}};
            if (i == tmp_snake.size() - 1 && tmp_snake[i - 1]->dir == UP)
                costume = {0, {3, 2}};
            if (i == tmp_snake.size() - 1 && tmp_snake[i - 1]->dir == DOWN)
                costume = {0, {4, 3}};

            if (i != tmp_snake.size() - 1 && s->dir == RIGHT)
                costume = {0, {1, 0}};
            if (i != tmp_snake.size() - 1 && s->dir == LEFT)
                costume = {0, {1, 0}};
            if (i != tmp_snake.size() - 1 && s->dir == UP)
                costume = {0, {2, 1}};
            if (i != tmp_snake.size() - 1 && s->dir == DOWN)
                costume = {0, {2, 1}};

            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == RIGHT && tmp_snake[i - 1]->dir == DOWN)
                costume = {0, {2, 0}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == RIGHT && tmp_snake[i - 1]->dir == UP)
                costume = {0, {2, 2}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == LEFT && tmp_snake[i - 1]->dir == DOWN)
                costume = {0, {0, 0}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == LEFT && tmp_snake[i - 1]->dir == UP)
                costume = {0, {0, 1}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == UP && tmp_snake[i - 1]->dir == RIGHT)
                costume = {0, {0, 0}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == UP && tmp_snake[i - 1]->dir == LEFT)
                costume = {0, {2, 0}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == DOWN && tmp_snake[i - 1]->dir == RIGHT)
                costume = {0, {0, 1}};
            if (i != tmp_snake.size() - 1 && i != 0 && s->dir == DOWN && tmp_snake[i - 1]->dir == LEFT)
                costume = {0, {2, 2}};


            if (i == 0 && s->dir == RIGHT && tmp_snake[i + 1])
                costume = {0, {4, 0}};
            if (i == 0 && s->dir == LEFT && tmp_snake[i + 1])
                costume = {0, {3, 1}};
            if (i == 0 && s->dir == UP && tmp_snake[i + 1])
                costume = {0, {3, 0}};
            if (i == 0 && s->dir == DOWN && tmp_snake[i + 1])
                costume = {0, {4, 1}};

            context.drawSprite(costume, s->x, s->y);
        }

        for (const auto &s: tmp_food) {
            arcade::SpriteCostume costume = {0, {0, 3}};

            context.drawSprite(costume, static_cast<size_t>(s->x), static_cast<size_t>(s->y));
        }

        arcade::SpriteCostume costume = {0, {1, 3}};
        for (int i = 0; i < _board->ymax; i++) {
            if (i == 0 || i == _board->ymax - 1) {
                for (int j = 0; j < _board->xmax; j++) {
                    context.drawSprite(costume, j, i);
                }
            } else {
                context.drawSprite(costume, 0, i);
                context.drawSprite(costume, _board->xmax - 1, i);
            }
        }
        context.drawText({ "Score: " + std::to_string(tmp_snake.size() - 4), WHITE, BLACK }, 0, _board->ymax + 1);
        if (_status == PAUSE)
            context.drawText({ "PAUSE", WHITE, BLACK }, 10, 20);
    }
    context.refreshWin();
}

extern "C" {
    game::Snake *entryPoint()
    {
        return new game::Snake;
    }

    arcade::LibType getType()
    {
        return arcade::LibType::GAME;
    }

    std::string getName()
    {
        return "Snake";
    }
}