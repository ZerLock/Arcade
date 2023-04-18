/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include "../../include/games/IGame.hpp"
#include "../types/Events.hpp"
#include "../types/Global.hpp"
#include "../types/Render.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>

static const auto LEVELONE = std::chrono::duration<double, std::ratio<1, FPS>>(5); /**<Speed for the ghost when level is 1>*/
static const auto LEVELTWO = std::chrono::duration<double, std::ratio<1, FPS>>(4); /**<Speed for the ghost when level is 2>*/
static const auto LEVELTHREE = std::chrono::duration<double, std::ratio<1, FPS>>(3); /**<Speed for the ghost when level is 3>*/
static const auto LEVELFOUR = std::chrono::duration<double, std::ratio<1, FPS>>(2); /**<Speed for the ghost when level is 4>*/

namespace game {

    /**
     * @brief Implementation of the Pacman game
     * 
     * The game is played on a board where the player controls a Pacman.
     * The goal is to eat all the dots on the board while avoiding the ghosts.
     * The player can move the Pacman with the arrow keys.
     * The game ends when the player touches a ghost or when all the dots are eaten.
     * If the player win the game, the level is increased and the game restarts.
     * If the player loose the game, his score is display and he can restart the game.
     * 
     * @see game::IGame
    */

    class Pacman: public game::IGame{
        public:

            /**
             * @brief Construct a new Pacman object
             * 
             * The constructor initialize the game.
             * It loads the spritesheets and the map.
             * It also initialize the ghosts.
             * 
            */
            Pacman();

            /**
             * @brief Destroy the Pacman object
             * 
            */
            ~Pacman();
            enum Direction {
                NONE,  /**< No direction. */
                UP,     /**< Up direction. */
                DOWN,   /**< Down direction. */
                LEFT,   /**< Left direction. */
                RIGHT   /**< Right direction. */
            };

            /**
            * @brief Enum defining the status of the game.
            */
            enum Status {
                SUCCESS, /**< The game action was successful. */
                FAILURE,  /**< The game action failed. */
                PAUSE /**< The game is paused. */
            };
            class IAGhost {
                public:

                    /**
                     * @brief Construct a new IAGhost object
                     * 
                     * The constructor initialize the ghost.
                     * It sets the ghost position and the ghost direction.
                     * 
                     * @param map The map of the game.
                     * @param nb The number of the ghost.
                    */
                    IAGhost() = default;
                    IAGhost(std::vector<std::vector<char>> map, char);

                    /**
                     * @brief Destroy the IAGhost object
                     * 
                    */
                    ~IAGhost();

                    /**
                     * @brief Get the Coords object
                     * 
                     * @return Coords The ghost position.
                    */
                    Coords getCoords() const;

                    /**
                     * @brief Move the ghost
                     * 
                     * The function move the ghost according to the ghost direction.
                     * 
                     * @param map The map of the game.
                    */
                    void moveGhost(std::vector<std::vector<char>> map);

                    /**
                     * @brief Check if the ghost is in colision with the pacman
                     * 
                     * @param pacman The pacman position.
                     * @return true If the ghost is in colision with the pacman.
                     * @return false If the ghost is not in colision with the pacman.
                    */
                    bool isColision(Coords pacman) const;

                    /**
                     * @brief Set the ghost direction
                     * 
                     * 
                     * Modify the direction of the ghost according to the pacman position.
                     * @param map The map of the game.
                     * @param pacman The pacman position.
                     * @param xmax The map width.
                     * @param ymax The map height.
                     * 
                    */
                    void modifyDir(std::vector<std::vector<char>> map, Coords pacman, std::size_t xmax, std::size_t ymax);

                    /**
                     * @brief Get the ghost direction
                     * 
                     * @return Direction The ghost direction.
                    */
                    Direction getDir() const;

                    /**
                     * @brief Get the ghost direction
                     * 
                     * @param map The map of the game.
                     * @param nb The number of the ghost.
                    */
                    Coords findGhost(std::vector<std::vector<char>> map, char nb) const;

                    /**
                     * @brief Getter for the _wlaked attribute
                     * 
                     * @return char The _walked attribute
                     *
                    */
                    char getWalked() const;

                    /**
                     * @brief Setter for the _walked attribute
                     * 
                     * @param c The new value of the _walked attribute
                     *
                    */
                    void setWalked(char);
                private:
                    Direction _dir; /**<Current direction of the ghost>*/
                    bool _isColision; /**<True if the ghost is in colision with the pacman, false otherwise>*/
                    Coords _pos; /**<Current position of the ghost>*/
                    char _walked; /**<The char erase by the ghost when moving>*/
            };

            /**
             * @brief Struct defining the board of the game.
             * 
             * The board is composed of a map, the pacman position and the map size.
            */
            struct Board {
                std::vector<std::vector<char>> map;
                Coords pacman;
                std::size_t xmax;
                std::size_t ymax;
            };

            /**
             * @brief find the start position of the pacman
             * 
             * @param board The board of the game.
             * @param c The char representing the pacman.
            */
            Coords findStart(Board board, char c);

            /**
             * @brief Initialize the map
             * 
             * @return std::vector<std::vector<char>> The map.
            */
            std::vector<std::vector<char>> initMap();

            /**
             * @brief Initialize the board
             * 
             * @return Board The board.
            */
            Board initBoard();

            /**
             * @brief Get the Spritesheets object
             *
             * @return const std::vector<arcade::Spritesheet>&
             */
            const std::vector<arcade::Spritesheet> &getSpritesheets() const;

            /**
             * @brief Set the new internal state of the game for the next tick
             *
             * @param std::chrono::duration<double>&
             * @param arcade::IContext&
             */
            void compute(std::chrono::duration<double> &dtime, arcade::IContext &context);

            /**
             * @brief Execute some code when an input is detected
             *
             * @param key
             */
            void handleInput(const arcade::KeyInput &key);

            /**
             * @brief Send to the IRenderer by IContext all the sprites to display on window with their new positions
             *
             * @param context
             */
            void render(arcade::IContext &context);

            /**
             * @brief Move the pacman according to the direction
             * 
             * @param context The context of the game.
            */
            void move(arcade::IContext &context);

            /**
             * @brief Change position of all the ghosts according to their direction
             * 
             * @param context The context of the game.
            */
            void moveAllGhosts(arcade::IContext &context);

            /**
             * @brief Check if the pacman have eat all the dots
             * 
             * @return true If the pacman have eat all the dots.
             * @return false If the pacman have not eat all the dots.
            */
            bool winCondition() const;

            /**
             * @brief Check if the pacman is in colision with a ghost
             * 
             * @param context The context of the game.
             * @return true If the pacman is in colision with a ghost.
             * @return false If the pacman is not in colision with a ghost.
            */
            bool looseCondition(arcade::IContext &context);
        protected:
        private:
            Board _board; /**<The board of the game>*/
            IAGhost _redGhost; /**<The red ghost>*/
            IAGhost _blueGhost; /**<The blue ghost>*/
            IAGhost _orangeGhost; /**<The orange ghost>*/
            IAGhost _pinkGhost; /**<The pink ghost>*/
            std::vector<arcade::Spritesheet> _sheets; /**<The spritesheets>*/
            std::chrono::duration<double> _deltaTime; /**<The time since the last tick>*/
            std::chrono::duration<double> _deltaTimeGhost; /**<The time since the last tick for the ghosts>*/
            Status _status; /**<The status of the game>*/
            int _score; /**<The score of the game>*/
            Direction _dir; /**<The direction of the pacman>*/
            Direction _lastDir; /**<The last direction of the pacman>*/
            short _level; /**<The level of the game>*/
    };
}

#endif /* !PACMAN_HPP_ */
