/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#define N_LEFT        260
#define N_RIGHT       261
#define N_UP          259
#define N_DOWN        258
#define N_SPACE       32
#define N_BACKSPACE   263
#define N_ESCAPE      27
#define N_ENTER       10

#include "IRenderer.hpp"
#include <ncurses.h>
#include <map>
#include <iostream>
#include <iostream>
#include <tuple>
#include <utility>

namespace render {

    /**
     * @class Ncurses
     * @brief A class that implements the IRenderer interface using the Ncurses library.
     *
     * The Ncurses class provides an implementation of the IRenderer interface using the Ncurses library.
     * It allows rendering of 2D graphics and handling user input. The renderer
     * uses a console-like interface for displaying graphics on the terminal.
     */
    class Ncurses: public render::IRenderer {
        public:
            /**
             * @brief Constructs a new Ncurses object and initializes the ncurses library.
             *
             * Initializes the ncurses library and sets up various settings such as hiding the cursor,
             * enabling the keypad, disabling echoing of input characters, and setting the terminal to
             * raw mode. Also sets up a mapping of ncurses key codes to arcade::RawKey enum values.
             */
            Ncurses();

            /**
            * @brief Destructor for the Ncurses class.
            *
            * This function cleans up the ncurses window and terminates ncurses mode.
            *
            */
            ~Ncurses() override;

            /**
             * @brief Load the sprite sheets used by the game.
             *
             * This function loads the sprite sheets used by the game into the rendering engine. It clears the current sprite vector
             * and then proceeds to parse each spritesheet in the provided vector. For each spritesheet, it reads a corresponding
             * text file that defines the characters and colors of each sprite in the sheet. It then creates a new sprite object for
             * each character in the file and adds it to the sprite vector along with its position on the screen and color pair. The
             * position of each sprite is determined by its location in the text file, and the color pair is determined by the
             * foreground and background colors defined in the text file. The index of the color pair corresponds to the index of the
             * spritesheet in the input vector.
             *
             * @param spritesheets A vector of spritesheets to load.
             */
            void loadSpritesheets(const std::vector<arcade::Spritesheet> &);

            /**
            * @brief Polls events from the Ncurses window.
            *
            * This function polls events from the Ncurses window, such as key presses, and converts them into a vector of arcade::Event structures.
            * If a valid key press is detected, it is mapped to an arcade::EventType using a mapping table stored in the _mapping member variable.
            * The resulting arcade::Event is then pushed to the inputs vector.
            *
            * @return A vector of arcade::Event structures representing the events polled from the Ncurses window.
            */
            std::vector<arcade::Event> pollEvents();

            /**
             * @brief Clears the window
             *
             */
            void clearWin();

            /**
            * @brief Refreshes the Ncurses window
            */
            void refreshWin();

            /**
             * @brief Draws a sprite onto the ncurses window.
             *
             * @param sprite The sprite to be drawn.
             * @param x The x coordinate of the top-left corner of the sprite.
             * @param y The y coordinate of the top-left corner of the sprite.
             */
            void drawSprite(const arcade::SpriteCostume &, double, double);

            /**
            * @brief Draws text on the screen at the given position in the given text style.
            *
            * This function uses the ncurses `mvprintw()` function to draw the text on the screen.
            * The text is drawn at the given coordinates (`x`, `y`) in the given `text` style.
            * The `x` and `y` coordinates are in pixel units.
            *
            * @param text The text to draw.
            * @param x The x-coordinate (in pixel units) where the text should be drawn.
            * @param y The y-coordinate (in pixel units) where the text should be drawn.
            */
            void drawText(const arcade::TextDisplay &, double, double);

        protected:
        private:
            /**
             * @brief Map of NCurses input keys to RawKey enum values.
             *
             * This map is used to convert input from the NCurses library to the
             * corresponding RawKey enum value from the arcade namespace.
             *
             * The keys of the map are integer values representing the input keys
             * from the NCurses library, and the values of the map are RawKey enum
             * values from the arcade namespace.
             */
            std::map<int, arcade::RawKey> _mapping;

            /**
             * @brief Struct representing a sprite in a terminal
             */
            struct NSprite {
                int foreground; /**< Foreground color of the sprite */
                int background; /**< Background color of the sprite */
                int color_pair; /**< Color pair index used by ncurses */
                int spritesheetIdx; /**< Index of the spritesheet this sprite belongs to */
                std::string sprite; /**< ASCII art of the sprite */
            } typedef NSprite;

        /**
        * @brief A vector of pairs representing the positions and the NSprites
        *
        * This vector contains pairs, where the first element is a Position struct that
        * represents the (x, y) position of the sprite, and the second element is an NSprite struct
        * that contains the sprite's foreground and background colors, its color pair, the index of
        * the spritesheet in which the sprite belongs to, and the actual character of the sprite.
        */
        std::vector<std::pair<Position, NSprite>> _spritesVector;
    };
}

#endif /* !NCURSES_HPP_ */
