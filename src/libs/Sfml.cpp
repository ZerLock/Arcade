/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include <iostream>

render::Sfml::Sfml()
    : _window(), _spritesheets(), _sprites(), _texts(), _font(), _mapping(), _colors()
{
    _window.create(sf::VideoMode::getDesktopMode(), "Sfml"); //, sf::Style::Fullscreen);
    _font.loadFromFile("./assets/graphicals/font.TTF");

    _mapping = {
        {sf::Keyboard::A, arcade::RawKey::K_A},
        {sf::Keyboard::B, arcade::RawKey::K_B},
        {sf::Keyboard::C, arcade::RawKey::K_C},
        {sf::Keyboard::D, arcade::RawKey::K_D},
        {sf::Keyboard::E, arcade::RawKey::K_E},
        {sf::Keyboard::F, arcade::RawKey::K_F},
        {sf::Keyboard::G, arcade::RawKey::K_G},
        {sf::Keyboard::H, arcade::RawKey::K_H},
        {sf::Keyboard::I, arcade::RawKey::K_I},
        {sf::Keyboard::J, arcade::RawKey::K_J},
        {sf::Keyboard::K, arcade::RawKey::K_K},
        {sf::Keyboard::L, arcade::RawKey::K_L},
        {sf::Keyboard::M, arcade::RawKey::K_M},
        {sf::Keyboard::N, arcade::RawKey::K_N},
        {sf::Keyboard::O, arcade::RawKey::K_O},
        {sf::Keyboard::P, arcade::RawKey::K_P},
        {sf::Keyboard::Q, arcade::RawKey::K_Q},
        {sf::Keyboard::R, arcade::RawKey::K_R},
        {sf::Keyboard::S, arcade::RawKey::K_S},
        {sf::Keyboard::T, arcade::RawKey::K_T},
        {sf::Keyboard::U, arcade::RawKey::K_U},
        {sf::Keyboard::V, arcade::RawKey::K_V},
        {sf::Keyboard::W, arcade::RawKey::K_W},
        {sf::Keyboard::X, arcade::RawKey::K_X},
        {sf::Keyboard::Y, arcade::RawKey::K_Y},
        {sf::Keyboard::Z, arcade::RawKey::K_Z},
        {sf::Keyboard::Space, arcade::RawKey::K_SPACE},
        {sf::Keyboard::Escape, arcade::RawKey::K_ESCAPE},
        {sf::Keyboard::Enter, arcade::RawKey::K_ENTER},
        {sf::Keyboard::Backspace, arcade::RawKey::K_BACKSPACE},
        {sf::Keyboard::Up, arcade::RawKey::K_UP},
        {sf::Keyboard::Down, arcade::RawKey::K_DOWN},
        {sf::Keyboard::Left, arcade::RawKey::K_LEFT},
        {sf::Keyboard::Right, arcade::RawKey::K_RIGHT},
    };

    _colors = {
        {BLACK, sf::Color::Black},
        {RED, sf::Color::Red},
        {GREEN, sf::Color::Green},
        {YELLOW, sf::Color::Yellow},
        {BLUE, sf::Color::Blue},
        {MAGENTA, sf::Color::Magenta},
        {CYAN, sf::Color::Cyan},
        {WHITE, sf::Color::White},
    };
}

render::Sfml::~Sfml()
{
    _window.close();
}

void render::Sfml::loadSpritesheets(const std::vector<arcade::Spritesheet> &spritesheets)
{
    _spritesheets.clear();
    for (auto &sheet : spritesheets) {
        sf::Texture texture;
        texture.loadFromFile(sheet.graphicPath);
        _spritesheets.push_back(std::make_tuple(sheet.unitDims, texture));
    }
}

std::vector<arcade::Event> render::Sfml::pollEvents()
{
    std::vector<arcade::Event> inputs;
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (auto key = _mapping.find(event.key.code); key != _mapping.end()) {
                inputs.push_back({ (*key).second, {0, 0} });
            }
        }
    }
    return inputs;
}

void render::Sfml::clearWin()
{
    _window.clear(sf::Color::Black);
}

void render::Sfml::refreshWin()
{
    _window.display();
}

void render::Sfml::drawSprite(const arcade::SpriteCostume &sprite, double x, double y)
{
    auto tmp = _spritesheets.at(sprite.spritesheet);
    auto dims = std::get<0>(tmp);
    sf::Sprite s;
    s.setTexture(std::get<1>(tmp));
    s.setTextureRect(sf::IntRect(sprite.pos.x * dims.x, sprite.pos.y * dims.y, dims.x, dims.y));
    s.setPosition(sf::Vector2f(x * (dims.x/4), y * (dims.y/4))); // TODO: use multiplier x0.25 to use in scale and coords
    s.scale(sf::Vector2f(0.25, 0.25));
    _window.draw(s);
}

void render::Sfml::drawText(const arcade::TextDisplay &text, double x, double y)
{
    sf::Text renderText;

    renderText.setFont(_font);
    renderText.setString(text.content);
    renderText.setCharacterSize(FONT_SIZE);
    renderText.setPosition(x * FONT_SIZE * 2, y * FONT_SIZE);
    renderText.setFillColor(_colors[text.fg]);
    renderText.setOutlineColor(_colors[text.bg]);
    _window.draw(renderText);
}

extern "C" {
    render::Sfml *entryPoint()
    {
        return new render::Sfml;
    }

    arcade::LibType getType()
    {
        return arcade::LibType::GRAPHICAL;
    }

    std::string getName()
    {
        return "Sfml";
    }
}
