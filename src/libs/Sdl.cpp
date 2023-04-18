/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** SDL
*/

#include "Sdl.hpp"

render::Sdl::Sdl()
    : _renderer(nullptr), _window(nullptr), _font(nullptr), _spritesheets(), _mapping(), _colors()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    // SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _font = TTF_OpenFont("./assets/graphicals/font.TTF", FONT_SIZE);

    _mapping = {
        {SDLK_a, arcade::RawKey::K_A},
        {SDLK_b, arcade::RawKey::K_B},
        {SDLK_c, arcade::RawKey::K_C},
        {SDLK_d, arcade::RawKey::K_D},
        {SDLK_e, arcade::RawKey::K_E},
        {SDLK_f, arcade::RawKey::K_F},
        {SDLK_g, arcade::RawKey::K_G},
        {SDLK_h, arcade::RawKey::K_H},
        {SDLK_i, arcade::RawKey::K_I},
        {SDLK_j, arcade::RawKey::K_J},
        {SDLK_k, arcade::RawKey::K_K},
        {SDLK_l, arcade::RawKey::K_L},
        {SDLK_m, arcade::RawKey::K_M},
        {SDLK_n, arcade::RawKey::K_N},
        {SDLK_o, arcade::RawKey::K_O},
        {SDLK_p, arcade::RawKey::K_P},
        {SDLK_q, arcade::RawKey::K_Q},
        {SDLK_r, arcade::RawKey::K_R},
        {SDLK_s, arcade::RawKey::K_S},
        {SDLK_t, arcade::RawKey::K_T},
        {SDLK_u, arcade::RawKey::K_U},
        {SDLK_v, arcade::RawKey::K_V},
        {SDLK_w, arcade::RawKey::K_W},
        {SDLK_x, arcade::RawKey::K_X},
        {SDLK_y, arcade::RawKey::K_Y},
        {SDLK_z, arcade::RawKey::K_Z},
        {SDLK_SPACE, arcade::RawKey::K_SPACE},
        {SDLK_ESCAPE, arcade::RawKey::K_ESCAPE},
        {SDLK_RETURN, arcade::RawKey::K_ENTER},
        {SDLK_BACKSPACE, arcade::RawKey::K_BACKSPACE},
        {SDLK_UP, arcade::RawKey::K_UP},
        {SDLK_DOWN, arcade::RawKey::K_DOWN},
        {SDLK_LEFT, arcade::RawKey::K_LEFT},
        {SDLK_RIGHT, arcade::RawKey::K_RIGHT},
    };

    _colors = {
        {BLACK, {0, 0, 0}},
        {RED, {255, 0, 0}},
        {GREEN, {0, 255, 0}},
        {YELLOW, {255, 255, 0}},
        {BLUE, {0, 0, 255}},
        {MAGENTA, {255, 0, 255}},
        {CYAN, {43, 250, 250}},
        {WHITE, {255, 255, 255}},
    };

}

render::Sdl::~Sdl()
{
    for (auto &tmp : _spritesheets) {
        SDL_DestroyTexture(std::get<1>(tmp));
    }
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void render::Sdl::loadSpritesheets(const std::vector<arcade::Spritesheet> &spriteList)
{
    for (auto &tmp : _spritesheets) {
        SDL_DestroyTexture(std::get<1>(tmp));
    }
    _spritesheets.clear();
    for (auto &sheet : spriteList) {
        SDL_Surface *surface = IMG_Load(sheet.graphicPath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        _spritesheets.push_back(std::make_tuple(sheet.unitDims, texture));
        SDL_FreeSurface(surface);
    }
}

std::vector<arcade::Event> render::Sdl::pollEvents()
{
    std::vector<arcade::Event> inputs;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (auto key = _mapping.find(event.key.keysym.sym); key != _mapping.end()) {
                inputs.push_back({ (*key).second, {0, 0} });
            }
        }
    }
    return inputs;
}

void render::Sdl::clearWin()
{
    SDL_RenderClear(_renderer);
}

void render::Sdl::refreshWin()
{
    SDL_RenderPresent(_renderer);
}

void render::Sdl::drawSprite(const arcade::SpriteCostume &sprite, double x, double y)
{
    auto tmp = _spritesheets.at(sprite.spritesheet);
    auto dims = std::get<0>(tmp);
    SDL_Rect srcrect = {static_cast<int>(sprite.pos.x * dims.x), static_cast<int>(sprite.pos.y * dims.y), static_cast<int>(dims.x), static_cast<int>(dims.y)};
    SDL_Rect dstrect = {static_cast<int>(x * (dims.x/4)), static_cast<int>(y * (dims.y/4)), static_cast<int>(dims.x/4), static_cast<int>(dims.y/4)};
    SDL_RenderCopy(_renderer, std::get<1>(tmp), &srcrect, &dstrect);
}

void render::Sdl::drawText(const arcade::TextDisplay &text, double x, double y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text.content.c_str(), _colors[text.fg]);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_Rect textRect;
    textRect.x = x * FONT_SIZE * 2;
    textRect.y = y * FONT_SIZE;
    textRect.w = text.content.size() * FONT_SIZE;
    textRect.h = FONT_SIZE;

    SDL_RenderCopy(_renderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

extern "C" {
    render::Sdl *entryPoint()
    {
        return new render::Sdl;
    }

    arcade::LibType getType()
    {
        return arcade::LibType::GRAPHICAL;
    }

    std::string getName()
    {
        return "Sdl2";
    }
}
