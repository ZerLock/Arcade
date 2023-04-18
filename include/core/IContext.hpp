/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** IContext
*/

#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <memory>
#include "../libs/IRenderer.hpp"
#include "../types/Events.hpp"
#include "../types/Render.hpp"

namespace arcade {

    class IContext {
        public:
            virtual ~IContext() = default;

            /**
             * @brief Link to the clearWin function of linked IRenderer
             *
             */
            virtual void clearWin() = 0;

            /**
             * @brief Link to the refreshWin function of linked IRenderer
             *
             */
            virtual void refreshWin() = 0;

            /**
             * @brief Link to the drawSprite function of linked IRenderer
             *
             * @param sprite
             * @param x
             * @param y
             */
            virtual void drawSprite(const SpriteCostume &sprite, double x, double y) = 0;

            /**
             * @brief Link to the drawText function of linked IRenderer
             *
             * @param text
             * @param x
             * @param y
             */
            virtual void drawText(const TextDisplay &text, double x, double y) = 0;

            /**
             * @brief Save the game score into a score file
             *
             * @param score
             */
            virtual void saveScore(const std::size_t &score) = 0;

        protected:
        private:
    };
}

#endif /* !ICONTEXT_HPP_ */
