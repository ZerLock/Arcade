/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "IGame.hpp"
#include <algorithm>

namespace game {

    class Menu: public game::IGame {
        public:
            Menu();
            ~Menu();

            /**
             * @brief Get the Spritesheets object
             *
             * @return const std::vector<arcade::Spritesheet>&
             */
            const std::vector<arcade::Spritesheet> &getSpritesheets() const;

            /**
             * @brief Set the new internal state of the menu for the next time
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
             * @brief Send to the IRenderer by IContext all the sprites to display on the window with their new positions
             *
             * @param context
             */
            void render(arcade::IContext &context);

            /**
             * @brief Set the scores
             *
             * @param scores
             */
            void setScores(std::map<std::string, std::vector<std::pair<std::string, std::size_t>>> scores);

            /**
             * @brief Pass from Core to Menu all the graphicals libraries path to display it
             *
             * @param libs
             * @param selectedLib
             */
            void setLibraries(std::vector<std::string> libs, std::size_t selectedLib);

            /**
             * @brief Pass from Core to Menu all the games libraries path to display it
             *
             * @param games
             */
            void setGames(std::vector<std::string> games);

            /**
             * @brief Pass from Core to Menu the username asked before launch Arcade
             *
             * @param username
             */
            void setUsername(const std::string &username);

            /**
             * @brief Get the Selected Game object
             *
             * @return std::size_t
             */
            std::size_t getSelectedGame() const;

            /**
             * @brief Get the Selected Lib object
             *
             * @return std::size_t
             */
            std::size_t getSelectedLib() const;

            /**
             * @brief Set the Selected Lib object
             *
             * @param index
             */
            void setSelectedLib(std::size_t index);

            /**
             * @brief Set the Selected Game object
             *
             * @param index
             */
            void setSelectedGame(std::size_t index);

        protected:
        private:
            std::vector<std::string> _libs;
            std::vector<std::string> _games;
            std::vector<arcade::Spritesheet> _spritesheets;
            std::string _username;
            std::size_t _selectedLib;
            std::size_t _preselectedLib;
            std::size_t _selectedGame;
            std::size_t _preselectedGame;
            std::chrono::duration<double> _deltaTime;
            std::size_t _globalX;
            std::map<std::string, std::vector<std::pair<std::string, std::size_t>>> _scores;

            /**
             * @brief Comparator function to use std::sort to sort std::pair by scores
             *
             * @param a
             * @param b
             * @return true
             * @return false
             */
            static bool _sortByScore(const std::pair<std::string, std::size_t> &a, const std::pair<std::string, std::size_t> &b);
    };
}

#endif /* !MENU_HPP_ */
