/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Global
*/

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define FPS 30

#include <cstddef>
#include <vector>
#include <map>
#include <chrono>

/**
 * @brief Framerate to cap the game movement
 *
 */
static const auto FRAMERATE = std::chrono::duration<double, std::ratio<1, FPS>>(3);

/**
 * @brief vector of vector, double array
 *
 * @tparam T
 */
template <typename T>
using matrix = std::vector<std::vector<T>>;

/**
 * @brief Position x and y used for spritesheets
 *
 */
struct Position {
    std::size_t x;
    std::size_t y;
};

/**
 * @brief Coords x and y used for graphical display and all other things except spritesheets
 *
 */
struct Coords {
    double x;
    double y;
};

/**
 * @brief Overloaded operator to compare two Coords structures
 *
 * @param coord1
 * @param coord2
 * @return true
 * @return false
 */
inline bool operator==(const Coords &coord1, const Coords &coord2)
{
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

/**
 * @brief Overloaded operator to compare two Position structures
 *
 * @param coord1
 * @param coord2
 * @return true
 * @return false
 */
inline bool operator==(const Position &coord1, const Position &coord2)
{
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

/**
 * @brief Overloaded operator to add two Coords structures
 *
 * @param coord1
 * @param coord2
 * @return Coords
 */
inline Coords operator+(const Coords &coord1, const Coords &coord2)
{
    Coords coo = {coord1.x + coord2.x, coord1.y + coord2.y};
    return coo;
}

/**
 * @brief Overloaded operator to concat two vector of type T
 *
 * @tparam T
 * @param vec1
 * @param vec2
 * @return std::vector<T>
 */
template <typename T>
inline std::vector<T> operator+(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    std::vector<T> vec = vec1;
    for (auto &elem : vec2)
        vec.push_back(elem);
    return vec;
}

/**
 * @brief Overloaded operator to add in the first Coords structure the second
 *
 * @param coord1
 * @param coord2
 * @return Coords&
 */
inline Coords &operator+=(Coords &coord1, const Coords &coord2)
{
    coord1.x += coord2.x;
    coord1.y += coord2.y;
    return coord1;
}

namespace arcade {
    /**
     * @brief Enum for differents libraries type
     *
     */
    enum LibType { GRAPHICAL = 1, GAME };
}

#endif /* !GLOBAL_HPP_ */
