/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SDL2
*/

#include "SDL2.hpp"

Libs::SDL2::SDL2()
{
    this->_open = true;
    this->_window = NULL;
    this->_renderer = NULL;
    this->_sprites = {};
    this->_fonts = {};
    this->_keyMap = {
        {SDLK_UNKNOWN, Arcade::KeyState::Unknown},
        {SDLK_LEFT, Arcade::KeyState::Left},
        {SDLK_RIGHT, Arcade::KeyState::Right},
        {SDLK_UP, Arcade::KeyState::Up},
        {SDLK_DOWN, Arcade::KeyState::Down},
        {SDLK_RETURN, Arcade::KeyState::Enter},
        {SDLK_ESCAPE, Arcade::KeyState::Escape},
        {SDLK_a, Arcade::KeyState::A},
        {SDLK_b, Arcade::KeyState::B},
        {SDLK_c, Arcade::KeyState::C},
        {SDLK_d, Arcade::KeyState::D},
        {SDLK_e, Arcade::KeyState::E},
        {SDLK_f, Arcade::KeyState::F},
        {SDLK_g, Arcade::KeyState::G},
        {SDLK_h, Arcade::KeyState::H},
        {SDLK_i, Arcade::KeyState::I},
        {SDLK_j, Arcade::KeyState::J},
        {SDLK_k, Arcade::KeyState::K},
        {SDLK_l, Arcade::KeyState::L},
        {SDLK_m, Arcade::KeyState::M},
        {SDLK_n, Arcade::KeyState::N},
        {SDLK_o, Arcade::KeyState::O},
        {SDLK_p, Arcade::KeyState::P},
        {SDLK_q, Arcade::KeyState::Q},
        {SDLK_r, Arcade::KeyState::R},
        {SDLK_s, Arcade::KeyState::S},
        {SDLK_t, Arcade::KeyState::T},
        {SDLK_u, Arcade::KeyState::U},
        {SDLK_v, Arcade::KeyState::V},
        {SDLK_w, Arcade::KeyState::W},
        {SDLK_x, Arcade::KeyState::X},
        {SDLK_y, Arcade::KeyState::Y},
        {SDLK_z, Arcade::KeyState::Z}};

        SDL_Init(SDL_INIT_EVERYTHING);
        if (TTF_Init() == -1)
            throw (SDLError("Unable to init SDL_ttf: " + std::string(TTF_GetError()), "Invalid TTF_Init"));
}

Libs::SDL2::~SDL2()
{
    for (auto it : this->_sprites)
        SDL_FreeSurface(it.second);
    TTF_Quit();
    SDL_Quit();
}

std::vector<Arcade::KeyEvent_t> Libs::SDL2::getEventsInit()
{
    std::vector<Arcade::KeyEvent_t> ret;

	while (SDL_PollEvent(&this->_event)) {   
 
        Arcade::KeyEvent_t tmp;
        int x, y = 0;
        tmp.key = Arcade::KeyState::Unknown;
        SDL_PumpEvents();
        SDL_GetMouseState(&x, &y);

        if (this->_event.type == SDL_KEYDOWN) {
            tmp.key = this->_keyMap[this->_event.key.keysym.sym];
            ret.push_back(tmp);
        }
    }
    return (ret);
}

void Libs::SDL2::checkPressedKey(Arcade::KeyEvent_t &keyEvent)
{
    switch (this->_event.key.keysym.sym)
    {
    case (SDLK_a):
    case (SDLK_z):
    case (SDLK_q):
    case (SDLK_s):
        break;
    default:
        keyEvent.key = this->_keyMap[this->_event.key.keysym.sym];
        break;
    }
}

void Libs::SDL2::checkPressedReleased(Arcade::KeyEvent_t &keyEvent)
{
    switch (this->_event.key.keysym.sym)
    {
    case (SDLK_a):
    case (SDLK_z):
    case (SDLK_q):
    case (SDLK_s):
        keyEvent.key = this->_keyMap[this->_event.key.keysym.sym];
        break;
    default:
        break;
    }
}

std::vector<Arcade::KeyEvent_t> Libs::SDL2::getEvents()
{
    std::vector<Arcade::KeyEvent_t> ret;

	while (SDL_PollEvent(&this->_event)) {   
        Arcade::KeyEvent_t tmp;
        int x, y = 0;
        tmp.key = Arcade::KeyState::Unknown;
        SDL_PumpEvents();
        SDL_GetMouseState(&x, &y);

        if (this->_event.type == SDL_KEYUP && 
        this->isPressEarly(this->_event.key.keysym.sym) == false) {
            this->checkPressedReleased(tmp);
        }
        if (this->_event.type == SDL_KEYDOWN) {
            this->checkPressedKey(tmp);
        }
        if (this->_event.type == SDL_QUIT) {
            this->close();
            this->_open = false;
        }
        tmp.x = x;
        tmp.y = y;
        ret.push_back(tmp);
    }
    return (ret);
}

void Libs::SDL2::init(std::string name, int w, int h)
{
    this->_window = SDL_CreateWindow( 
        name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
  	);

    if (this->_window == NULL)
        throw (SDLError("Unable to create the window: " + std::string(SDL_GetError()), "Invalid Window"));
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    this->_keyInit = this->getEventsInit();
}

bool Libs::SDL2::isPressEarly(Sint32 key)
{
    for (std::size_t t = 0; t < this->_keyInit.size(); t++) {
        if (this->_keyInit[t].key == this->_keyMap[key]) {
            this->_keyInit[t].key = Arcade::KeyState::Unknown;
            return (true);
        }
    }
    return (false);
}

bool Libs::SDL2::isOpen() const
{
    return (this->_open);
}

void Libs::SDL2::close()
{
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
}

bool Libs::SDL2::drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
    Arcade::Rect_t shape;
    bool ret = false;

    for (const auto it: shapes) {
        shape = it.second;
        SDL_Rect dest = {shape.x, shape.y, shape.w, shape.h};

        if (shape.layer != layer)
            continue;

        ret = true;
        SDL_SetRenderDrawColor(this->_renderer, shape.bg.r, shape.bg.g, shape.bg.b, shape.bg.a);
        SDL_RenderDrawRect(this->_renderer, &dest);
        SDL_RenderFillRect(this->_renderer, &dest);
    }

    return (ret);
}

bool Libs::SDL2::drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
    std::string key = "";
    SDL_Surface *spriteSurface = NULL;
    Arcade::Sprites_t spriteData;
    bool ret = false;

    for (const auto it: sprites) {
        key = it.first;
        spriteData = it.second;

        if (spriteData.layer != layer)
            continue;

        if (this->_sprites.count(key)) {
            spriteSurface = this->_sprites[key];
        } else {
            spriteSurface = IMG_Load((spriteData.path + ".png").c_str());
            this->_sprites[key] = spriteSurface;
        }
        if (spriteSurface == NULL)
            throw (SDLError("Unable to load the sprite " + std::string(SDL_GetError()), "Invalid sprite"));
        
        ret = true;
        SDL_Rect src = {spriteData.rect.x, spriteData.rect.y, spriteData.rect.w, spriteData.rect.h};
        SDL_Rect dest = {spriteData.x, spriteData.y, spriteData.rect.w, spriteData.rect.h};
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, spriteSurface);
        SDL_RenderCopy(this->_renderer, texture, &src, &dest);
        SDL_DestroyTexture(texture);
    }

    return (ret);
}

bool Libs::SDL2::drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
    std::string key = "";
    TTF_Font *font = NULL;
    Arcade::Text_t text;
    bool ret = false;

    for (const auto it: texts) {
        key = it.first;
        text = it.second;

        if (text.layer != layer)
            continue;

        if (this->_fonts.count(key)) {
            font = this->_fonts[key];
        } else {
            font = TTF_OpenFont(text.font.c_str(), text.size);
            this->_fonts[key] = font;
        }

        ret = true;
        SDL_Color foregroundColor = {
            static_cast<Uint8>(text.colorText.r),
            static_cast<Uint8>(text.colorText.g),
            static_cast<Uint8>(text.colorText.b),
            static_cast<Uint8>(text.colorText.a)
        };
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.text.c_str(), foregroundColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
        SDL_Rect dest = {text.x, text.y, textSurface->w, textSurface->h};
        SDL_RenderCopy(this->_renderer, texture, NULL, &dest);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
    }

    return(ret);
}

void Libs::SDL2::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
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

void Libs::SDL2::display() const
{
    SDL_RenderPresent(this->_renderer);
}

void Libs::SDL2::my_clear() const
{
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);
}

void Libs::SDL2::setSizePixel(std::pair<int, int> size)
{
    return;
}

void Libs::SDL2::setSizeWindows(std::pair<int, int> size)
{
    SDL_SetWindowSize(this->_window, size.first, size.second);
}