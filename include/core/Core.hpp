/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>
#include <thread>
#include <map>
#include "DLLoader.hpp"
#include "../libs/IRenderer.hpp"
#include "../games/IGame.hpp"
#include "Menu.hpp"
#include "Error.hpp"
#include "Context.hpp"

namespace arcade {
    class Context;
    enum RawKey;
    enum Keymaps;
}

namespace core {

    class Core {
        public:
            Core(const std::string &firstLib);
            ~Core();

            /**
             * @brief Change graphic library
             *
             * @param index
             */
            void changeLib(std::size_t index);

            /**
             * @brief Change game library
             *
             * @param index
             */
            void changeGame(std::size_t index);

            /**
             * @brief Core loop, main loop of the Arcade
             *
             */
            void coreLoop();

            /**
             * @brief Handle core inputs
             *
             */
            void coreHandleInputs(std::vector<arcade::KeyInput> keys);

            /**
             * @brief Get the Renderer object
             *
             * @return render::IRenderer*&
             */
            render::IRenderer *&getRenderer();

            /**
             * @brief Save the game score into a score file
             *
             * @param score
             */
            void saveScore(const std::size_t &score);

            /**
             * @brief Load score from assets/score.txt and save it in a map of vector
             *
             */
            void loadScore();

            /**
             * @brief Get the Mapping object
             *
             * @return std::map<arcade::RawKey, arcade::Keymaps>
             */
            std::map<arcade::RawKey, arcade::Keymaps> getMapping() const;

            /**
             * @brief Convert RawKey to KeyInput
             *
             * @param keys
             * @return std::vector<arcade::Event>
             */
            std::vector<arcade::KeyInput> _mapEvents(std::vector<arcade::Event> keys);

            /**
             * @brief Return to Arcade menu
             *
             */
            void _goToMenu();

            /**
             * @brief Get delta Time from the frame start
             *
             * @return std::chrono::duration<double>
             */
            std::chrono::duration<double> _timer();

            /**
             * @brief Get the correct firstLib path (handle static path ex: lib/arcade...)
             *
             * @param path
             * @return std::string
             */
            std::string _getLibPath(const std::string &path);

            /**
             * @brief Get all graphics and games libraries
             *
             * @param firstLib
             */
            void _getLibraries(const std::string &firstLib);

        protected:
        private:
            std::unique_ptr<arcade::Context> _context;
            core::DLLoader _libLoader;
            core::DLLoader _gameLoader;
            render::IRenderer *_lib;
            game::IGame *_game;
            game::Menu *_menu;
            std::size_t _currentLibIndex;
            std::size_t _currentGameIndex;
            std::vector<std::string> _libs;
            std::vector<std::string> _games;
            std::map<arcade::RawKey, arcade::Keymaps> _inputsMap;
            bool _isRunning;
            bool _isInMenu;
            std::chrono::time_point<std::chrono::steady_clock> _frameStart;
            std::string _username;

            /**
             * [Snake, [{"Leo", 4}, {"Maxime", 8}, {"Thomas", 24}]]
             * [Pacman, [{"Maxime", 256}, {"Leo", 48}, {"Thomas", 78}]]
             */
            std::map<std::string, std::vector<std::pair<std::string, std::size_t>>> _scores;
            std::vector<std::string> _menuLibs;
            std::vector<std::string> _menuGames;

            /**
             * @brief Split string by a delimiter (by default ' ')
             *
             * @param str
             * @param delim
             * @return std::vector<std::string>
             */
            std::vector<std::string> _mySplit(const std::string &str, char delim = ' ') const;
    };
}

#endif /* !CORE_HPP_ */
