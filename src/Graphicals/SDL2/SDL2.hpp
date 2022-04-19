/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SDL2
*/

#ifndef __SDL2_HPP__
    #define __SDL2_HPP__

    #include <memory>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <map>

    #include "../GraphicsErrors.hpp"
    #include "../DisplayModule.hpp"

namespace Libs {
    class SDL2 : public DisplayModule {

        public:
            SDL2();
            ~SDL2();

            std::vector<Arcade::KeyEvent_t> getEvents();
            std::vector<Arcade::KeyEvent_t> getEventsInit();
            void init(std::string name, int w, int h);

            void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, 
            std::unordered_map<std::string, Arcade::Sprites_t> sprites,
            std::unordered_map<std::string, Arcade::Text_t> texts);
    
            bool drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            bool drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            bool drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);
    
            bool isPressEarly(Sint32 key);
            void checkPressedKey(Arcade::KeyEvent_t &keyEvent);
            void checkPressedReleased(Arcade::KeyEvent_t &keyEvent);

            bool isOpen() const;
            void display() const;
            void close();
            void my_clear() const;
    
            void setSizePixel(std::pair<int, int> size);
            void setSizeWindows(std::pair<int, int> size);
        
        private:
            std::map<std::string, SDL_Surface *> _sprites;
            std::map<std::string, TTF_Font *> _fonts;
            std::map<Sint32, Arcade::KeyState> _keyMap;
            std::vector<Arcade::KeyEvent_t> _keyInit;

            SDL_Event event;
            SDL_Window *_window;
            SDL_Renderer* _renderer;
            SDL_Event _event;

            bool _open;
    };
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create()
    {
        return (std::make_shared<Libs::SDL2>());
    }
}

#endif /* !SDL2_HPP_ */
