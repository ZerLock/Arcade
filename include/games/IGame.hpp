/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <cstddef>
#include <vector>
#include "../types/Events.hpp"
#include "../types/Render.hpp"
#include "../libs/IRenderer.hpp"
#include "../core/IContext.hpp"

namespace game {

    class IGame {
        public:
            virtual ~IGame() = default;

            /**
             * @brief Get the Spritesheets object
             *
             * @return const std::vector<arcade::Spritesheet>&
             */
            virtual const std::vector<arcade::Spritesheet> &getSpritesheets() const = 0;

            /**
             * @brief Set the new internal state of the game for the next tick
             *
             * @param std::chrono::duration<double>&
             * @param arcade::IContext&
             */
            virtual void compute(std::chrono::duration<double> &dtime, arcade::IContext &context) = 0;

            /**
             * @brief Execute some code when an input is detected
             *
             * @param key
             */
            virtual void handleInput(const arcade::KeyInput &key) = 0;

            /**
             * @brief Send to the IRenderer by IContext all the sprites to display on window with their new positions
             *
             * @param context
             */
            virtual void render(arcade::IContext &context) = 0;

        protected:
        private:
    };
}

#endif /* !IGAME_HPP_ */
