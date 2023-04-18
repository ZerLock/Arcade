/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** AContext
*/

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include "../core/Core.hpp"
#include "IContext.hpp"

namespace core {
    class Core;
}

namespace arcade {

    class Context: public IContext {
        public:
            Context(core::Core &core);
            ~Context();

            /**
             * @brief Link to the clearWin function of linked IRenderer
             *
             */
            void clearWin();

            /**
             * @brief Link to the refreshWin function of linked IRenderer
             *
             */
            void refreshWin();

            /**
             * @brief Link to the drawSprite function of linked IRenderer
             *
             * @param sprite
             * @param x
             * @param y
             */
            void drawSprite(const arcade::SpriteCostume &sprite, double x, double y);

            /**
             * @brief Link to the drawText function of linked IRenderer
             *
             * @param text
             * @param x
             * @param y
             */
            void drawText(const arcade::TextDisplay &text, double x, double y);

            /**
             * @brief Save the game score into a score file
             *
             * @param score
             */
            void saveScore(const std::size_t &score);

        protected:
        private:
            core::Core &_core;
    };
}

#endif /* !CONTEXT_HPP_ */
