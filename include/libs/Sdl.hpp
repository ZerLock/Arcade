/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** SDL
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "IRenderer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <tuple>

namespace render {

    class Sdl: public render::IRenderer {
        public:
            Sdl();
            ~Sdl() override;

            /**
             * @brief Load SDL spritesheet from common Arcade Spritesheet
             *
             * @param const std::vector<arcade::Spritesheet>&
             */
            void loadSpritesheets(const std::vector<arcade::Spritesheet> &);

            /**
             * @brief Get inputs events from SDL poll events
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
            SDL_Renderer *_renderer;
            SDL_Window *_window;
            TTF_Font *_font;
            std::vector<std::tuple<Position, SDL_Texture *>> _spritesheets;
            std::map<SDL_Keycode, arcade::RawKey> _mapping;
            std::map<char, SDL_Color> _colors;
    };
}

#endif /* !SDL_HPP_ */
