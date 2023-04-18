/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** IRenderer
*/

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <vector>
#include "../types/Events.hpp"
#include "../types/Render.hpp"

namespace render {

    class IRenderer {
        public:
            virtual ~IRenderer() = default;

            /**
             * @brief Load lib spritesheet from common Arcade Spritesheet
             *
             * @param const std::vector<arcade::Spritesheet>&
             */
            virtual void loadSpritesheets(const std::vector<arcade::Spritesheet> &) = 0;

            /**
             * @brief Get inputs event from lib
             *
             * @return std::vector<arcade::Event>
             */
            virtual std::vector<arcade::Event> pollEvents() = 0;

            /**
             * @brief Clear window
             *
             */
            virtual void clearWin() = 0;

            /**
             * @brief Update the new status of the window
             *
             */
            virtual void refreshWin() = 0;

            /**
             * @brief Draw sprite at coords x and y on the window
             *
             * @param const arcade::SpriteCostume&
             * @param double
             * @param double
             */
            virtual void drawSprite(const arcade::SpriteCostume &, double, double) = 0;

            /**
             * @brief Draw text at coords x and y on the window
             *
             * @param const arcade::TextDisplay&
             * @param double
             * @param double
             */
            virtual void drawText(const arcade::TextDisplay &, double, double) = 0;

        protected:
        private:
    };
}

#endif /* !IRENDERER_HPP_ */
