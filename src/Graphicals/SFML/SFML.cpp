/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SFML
*/

#include "SFML.hpp"
#include "../../Core/Interoperability.hpp"

Libs::SFML::SFML()
{
    this->_open = true;
    this->_window = nullptr;
    this->_fonts = {};
    this->_keyMap = {
        {sf::Keyboard::Unknown, Arcade::KeyState::Unknown},
        {sf::Keyboard::Left, Arcade::KeyState::Left},
        {sf::Keyboard::Right, Arcade::KeyState::Right},
        {sf::Keyboard::Up, Arcade::KeyState::Up},
        {sf::Keyboard::Down, Arcade::KeyState::Down},
        {sf::Keyboard::Enter, Arcade::KeyState::Enter},
        {sf::Keyboard::Escape, Arcade::KeyState::Escape},
        {sf::Keyboard::A, Arcade::KeyState::A},
        {sf::Keyboard::B, Arcade::KeyState::B},
        {sf::Keyboard::C, Arcade::KeyState::C},
        {sf::Keyboard::D, Arcade::KeyState::D},
        {sf::Keyboard::E, Arcade::KeyState::E},
        {sf::Keyboard::F, Arcade::KeyState::F},
        {sf::Keyboard::G, Arcade::KeyState::G},
        {sf::Keyboard::H, Arcade::KeyState::H},
        {sf::Keyboard::I, Arcade::KeyState::I},
        {sf::Keyboard::J, Arcade::KeyState::J},
        {sf::Keyboard::K, Arcade::KeyState::K},
        {sf::Keyboard::L, Arcade::KeyState::L},
        {sf::Keyboard::M, Arcade::KeyState::M},
        {sf::Keyboard::N, Arcade::KeyState::N},
        {sf::Keyboard::O, Arcade::KeyState::O},
        {sf::Keyboard::P, Arcade::KeyState::P},
        {sf::Keyboard::Q, Arcade::KeyState::Q},
        {sf::Keyboard::R, Arcade::KeyState::R},
        {sf::Keyboard::S, Arcade::KeyState::S},
        {sf::Keyboard::T, Arcade::KeyState::T},
        {sf::Keyboard::U, Arcade::KeyState::U},
        {sf::Keyboard::V, Arcade::KeyState::V},
        {sf::Keyboard::W, Arcade::KeyState::W},
        {sf::Keyboard::X, Arcade::KeyState::X},
        {sf::Keyboard::Y, Arcade::KeyState::Y},
        {sf::Keyboard::Z, Arcade::KeyState::Z}};
}

Libs::SFML::~SFML()
{
}

void Libs::SFML::init(std::string name, int w, int h)
{
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(w, h), name);
    this->getEventsInit();
}

bool Libs::SFML::isPressEarly(sf::Keyboard::Key key)
{
    if (this->_keyInit[key]) {
        this->_keyInit[key] = false;
        return (true);
    }
    return (false);
}

void Libs::SFML::getEventsInit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->_keyInit[sf::Keyboard::A] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        this->_keyInit[sf::Keyboard::Z] = true;
}

void Libs::SFML::checkPressedKey(Arcade::KeyEvent_t &keyEvent)
{
    switch (this->_event.key.code)
    {
    case (sf::Keyboard::A):
    case (sf::Keyboard::Z):
    case (sf::Keyboard::Q):
    case (sf::Keyboard::S):
        break;
    default:
        keyEvent.key = this->_keyMap[this->_event.key.code];
        break;
    }
}

void Libs::SFML::checkPressedReleased(Arcade::KeyEvent_t &keyEvent)
{
    switch (this->_event.key.code)
    {
    case (sf::Keyboard::A):
    case (sf::Keyboard::Z):
    case (sf::Keyboard::Q):
    case (sf::Keyboard::S):
        keyEvent.key = this->_keyMap[this->_event.key.code];
        break;
    default:
        break;
    }
}

std::vector<Arcade::KeyEvent_t> Libs::SFML::getEvents()
{
    std::vector<Arcade::KeyEvent_t> ret;
    Arcade::KeyEvent_t tmp;

    while ((*this->_window.get()).pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed) {
            this->close();
            this->_open = false;
        }

        sf::Vector2i mPos = sf::Mouse::getPosition();
        tmp.x = mPos.x;
        tmp.y = mPos.y;
        tmp.key = Arcade::KeyState::Unknown;

        if ((this->_event.type == sf::Event::KeyReleased) && 
        (this->isPressEarly(this->_event.key.code) == false)) {
            this->checkPressedReleased(tmp);
        }
        if (this->_event.type == sf::Event::KeyPressed) {
            this->checkPressedKey(tmp);
        }
        ret.push_back(tmp);
    }
    return (ret);
}

bool Libs::SFML::isOpen() const
{
    return (this->_open);
}

void Libs::SFML::close()
{
    if (this->_window.get())
        (*this->_window.get()).close();
}

bool Libs::SFML::drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
    sf::RectangleShape rect;
    Arcade::Rect_t shape;
    bool ret = false;

    for (const auto it: shapes) {
        shape = it.second;
        rect = sf::RectangleShape(sf::Vector2f(shape.w, shape.h));

        if (shape.layer != layer)
            continue;
        
        ret = true;
        rect.setPosition(sf::Vector2f(shape.x, shape.y));
        rect.setFillColor(sf::Color(shape.bg.r, shape.bg.g, shape.bg.b, shape.bg.a));
        this->_window.get()->draw(rect);
    }

    return (ret);
}

bool Libs::SFML::drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
    std::string key = "";
    sf::Texture texture;
    sf::Sprite sprite;
    Arcade::Sprites_t spriteData;
    bool ret = false;

    for (const auto it: sprites) {
        key = it.first;
        spriteData = it.second;

        if (spriteData.layer != layer)
            continue;

        if (this->_sprites.count(key)) {
            texture = this->_sprites[key];
        } else {
            if (texture.loadFromFile(spriteData.path + ".png") == false)
                throw (SFMLError("Unable to load " + spriteData.path + ".png", "Invalid image"));
            this->_sprites[key] = texture;
        }

        ret = true;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(spriteData.rect.x, spriteData.rect.y, spriteData.rect.w, spriteData.rect.h));
        sprite.setPosition(spriteData.x, spriteData.y);
        this->_window.get()->draw(sprite);
    }

    return (ret);
}

bool Libs::SFML::drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
    std::string key = "";
    sf::Font font;
    Arcade::Text_t textData;
    sf::Text text;
    sf::Uint32 color = 0;
    bool ret = false;

    for (const auto it: texts) {
        key = it.first;
        textData = it.second;

        if (textData.layer != layer)
            continue;

        if (this->_fonts.count(key)) {
            font = this->_fonts[key];
        } else {
            font.loadFromFile(textData.font);
            this->_fonts[key] = font;
        }

        ret = true;
        text.setFont(font);
        text.setString(textData.text);
        text.setCharacterSize(textData.size);
        text.setPosition(sf::Vector2f(textData.x, textData.y));

        color = static_cast<sf::Uint8>(textData.colorText.r);
        color <<= 8;
        color += static_cast<sf::Uint8>(textData.colorText.g);
        color <<= 8;
        color += static_cast<sf::Uint8>(textData.colorText.b);
        color <<= 8;
        color += static_cast<sf::Uint8>(textData.colorText.a);

        text.setFillColor(sf::Color(color));
        this->_window.get()->draw(text);
    }

    return (ret);
}

void Libs::SFML::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
{
    size_t layer = 0;
    bool draw = true;

    while (draw == true) {
        draw = false;
        draw |= this->drawShapes(shapes, layer);
        draw |= this->drawSprites(sprites, layer);
        draw |= this->drawTexts(texts, layer);
        layer++;
    }
}

void Libs::SFML::my_clear() const
{
    this->_window.get()->clear(sf::Color::Black);
}

void Libs::SFML::display() const
{
    this->_window.get()->display();
}

void Libs::SFML::setSizePixel(std::pair<int, int> size)
{
    return;
}

void Libs::SFML::setSizeWindows(std::pair<int, int> size)
{
    sf::Uint32 w = size.first;
    sf::Uint32 h = size.second;
    const sf::Vector2u newSize = {w, h};
    sf::FloatRect visibleArea(0, 0, w, h);

    this->_window.get()->setSize(newSize);
    this->_window.get()->setView(sf::View(visibleArea));
}