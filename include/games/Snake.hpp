/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <vector>
#include <cstddef>
#include "IGame.hpp"

namespace game {

    /**
     * @brief Implementation of the Snake game.
     *
     * The game is played on a board where the player controls a snake that grows as it eats food.
     * The objective of the game is to eat as much food as possible without colliding with the walls or the snake's body.
     *
     * @see game::IGame
     */
    class Snake: public game::IGame {
        public:

            /**
             * @brief Constructor for the Snake game.
             *
             * Initializes the _sheets vector with a single Spritesheet object, sets _deltaTime to 0, sets _dir to RIGHT,
             * creates a new Board object by calling the create_board function with a newly created snake and an empty vector of foods,
             * sets _board to point to this newly created object. Finally, calls the add_food function 5 times to add 5 foods to the board.
             */
            Snake();
            /**
            * @brief Destructor for the Snake class.
            */
            ~Snake();

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

        protected:
            /**
            * @brief The Direction enum represents the four cardinal directions.
            */
            enum Direction {
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

            /**
             * @brief Struct representing a single cell in the game board.
             */
            struct Cells {
                int x; /**< The x-coordinate of the cell. */
                int y; /**< The y-coordinate of the cell. */
                Direction dir; /**< The direction the cell is facing. */
            } typedef Cells;

            /**
            * @brief Struct representing the game board for Snake.
            */
            struct Board {
                std::vector<Cells *> snake; /**< The snake's body represented as a vector of Cells pointers */
                std::vector<Cells *> foods; /**< The food items on the board represented as a vector of Cells pointers */
                int xmax; /**< The maximum x-coordinate value of the board */
                int ymax; /**< The maximum y-coordinate value of the board */
            } typedef Board;

            /**
             * @brief Checks if the given cell is in the given vector of cells.
             *
             * @param cell The cell to check.
             * @param vec The vector of cells to check in.
             * @return Returns true if the cell is in the vector, false otherwise.
             */
            static bool is_same_place(Cells *cell1, Cells *cell2);

            /**
             * @brief Moves the snake in the specified direction
             *
             * This function moves the snake in the specified direction and updates the game board accordingly. If the move is invalid or the snake collides with itself, the game ends.
             *
             * @param board A pointer to the board object
             * @param dir The direction that the snake should move in
             *
             * @return Returns the status of the game after the move has been made (SUCCESS or FAILURE).
             */
            enum Status move_snake(Board *board, enum Direction dir);

            /**
             * @brief Calculates the next move of the snake
             *
             * This function calculates the coordinates of the next move of the snake based on its current direction and the size of the board.
             *
             * @param board A pointer to the board object
             * @param dir The direction that the snake is currently facing
             *
             * @return Returns a pointer to a new cell object representing the next move of the snake, or nullptr if the move is invalid.
             */
            static Cells *get_next_move(Board *board, enum Direction dir);

            /**
             * @brief Creates a new cell object
             *
             * This function creates a new cell object with the specified x and y coordinates and direction.
             *
             * @param x The x-coordinate value of the cell
             * @param y The y-coordinate value of the cell
             * @param dir The direction that the cell is facing
             *
             * @return Returns a pointer to the newly created cell object.
             */
            static Cells *create_cell(int x, int y, enum Direction dir);

            /**
             * @brief Creates a new cell with random coordinates
             *
             * This function creates a new cell with random x and y coordinates within the specified dimensions, and facing upwards.
             *
             * @param xmax The maximum x-coordinate value of the board
             * @param ymax The maximum y-coordinate value of the board
             *
             * @return Returns a pointer to the newly created cell object.
             */
            static Cells *create_cell_rand(int xmax, int ymax);

            /**
             * @brief Creates a new snake
             *
             * This function creates a new snake consisting of four cells at the specified coordinates, all facing to the right.
             *
             * @return Returns a vector containing pointers to the cells that make up the snake.
             */
            static std::vector<Cells *> create_snake();

            /**
             * @brief Creates a new board object
             *
             * This function creates a new board object with the specified snake and food items, and sets the board's size to the specified dimensions.
             *
             * @param snake A vector containing pointers to the cells that make up the snake
             * @param foods A vector containing pointers to the cells that make up the food items
             * @param xmax The maximum x-coordinate value of the board
             * @param ymax The maximum y-coordinate value of the board
             *
             * @return Returns a pointer to the newly created board object.
             */
            static Board *create_board(std::vector<game::Snake::Cells *> snake, std::vector<game::Snake::Cells *> foods, int xmax, int ymax);

            /**
             * @brief Checks whether a vector contains a specified cell
             *
             * This function searches for the first occurrence of the given cell in the specified vector and returns true if found; false otherwise. The vector should contain pointers to objects of type Cells.
             *
             * @param cell The cell to search for in the vector
             * @param vec The vector in which to search for the cell
             *
             * @return Returns true if the vector contains the specified cell; false otherwise.
             */
            static bool list_contains(Cells *cell, const std::vector<game::Snake::Cells *>& list);

            /**
             * @brief Removes the specified element from a vector and deallocates its memory
             *
             * This function searches for the first occurrence of the given element in the specified vector and removes it from the vector if found. It also deallocates the memory used by the element. The vector should contain pointers to objects of type Cells.
             *
             * @param elt The element to be removed from the vector
             * @param vec The vector from which the element should be removed
             *
             * @return Returns true if the element was found and removed from the vector; false otherwise.
             */
            static bool remove_from_list(Cells *elt, std::vector<Cells*>& vec);

            /**
            * @brief Adds a new food to the board
            *
            * This function creates a new food object and adds it to the board's list of food items. The food is placed at a random position on the board that is not already occupied by the snake or another food item.
            *
            * @param board A pointer to the board on which to add the food
            */
            static void add_food(Board *board);

            /**
             * @brief Restarts the game
             *
             * This function resets the game's state to its initial state. It sets the snake's direction to RIGHT, sets the game's status to SUCCESS, creates a new board with a new snake and no food items, and then adds 5 new food items to the board.
             */
            void restart();

        private:
            std::vector<arcade::Spritesheet> _sheets; /**< Vector of Spritesheets used for rendering the game */
            Board* _board; /**< Pointer to the game board */
            std::chrono::duration<double> _deltaTime{}; /**< Time duration between each frame */
            enum Direction _dir; /**< Current direction of the snake */
            enum Direction _lastDir; /**< Previous direction of the snake */
            enum Status _status; /**< Current status of the game */
    };
}

#endif /* !SNAKE_HPP_ */
