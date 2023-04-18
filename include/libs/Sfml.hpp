/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>

namespace render {

    class Sfml: public render::IRenderer {
        public:
            Sfml();
            ~Sfml() override;

            /**
             * @brief Load SFML spritesheet from common Arcade Spritesheet
             *
             * @param const std::vector<arcade::Spritesheet>&
             */
            void loadSpritesheets(const std::vector<arcade::Spritesheet> &);

            /**
             * @brief Get inputs events from SFML poll events
             *
             * @return std::vector<arcade::Event>
             */
            std::vector<arcade::Event> pollEvents();

            /**
             * @brief Clear window
             *
             */
            void clearWin();

            /**
             * @brief Update the new status of the window
             *
             */
            void refreshWin();

            /**
             * @brief Draw sprite at coords x and y on the window
             *
             * @param const arcade::SpriteCostume&
             * @param double
             * @param double
             */
            void drawSprite(const arcade::SpriteCostume &, double, double);

            /**
             * @brief Draw text at coords x and y on the window
             *
             * @param const arcade::TextDisplay&
             * @param double
             * @param double
             */
            void drawText(const arcade::TextDisplay &, double, double);

        protected:
        private:
            sf::RenderWindow _window;
            std::vector<std::tuple<Position, sf::Texture>> _spritesheets;
            std::vector<arcade::SpriteCostume> _sprites;
            std::vector<arcade::TextDisplay> _texts;
            sf::Font _font;
            std::map<sf::Keyboard::Key, arcade::RawKey> _mapping;
            std::map<char, sf::Color> _colors;
    };
}

#endif /* !SFML_HPP_ */
