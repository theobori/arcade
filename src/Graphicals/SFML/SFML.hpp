/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SFML
*/

#ifndef __SFML_HPP__
    #define __SFML_HPP__

    #include <memory>
    #include <SFML/Graphics.hpp>

    #include "../DisplayModule.hpp"
    #include "../GraphicsErrors.hpp"

namespace Libs {
    class SFML : public DisplayModule {

        public:
            SFML();
            ~SFML();

            std::vector<Arcade::KeyEvent_t> getEvents();
            void getEventsInit();
            void init(std::string name, int w, int h);

            void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, 
            std::unordered_map<std::string, Arcade::Sprites_t> sprites,
            std::unordered_map<std::string, Arcade::Text_t> texts);

            bool drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            bool drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            bool drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);

            bool isPressEarly(sf::Keyboard::Key key);
            void checkPressedKey(Arcade::KeyEvent_t &keyEvent);
            void checkPressedReleased(Arcade::KeyEvent_t &keyEvent);

            bool isOpen() const;
            void close();
            void my_clear() const;
            void display() const;

            void setSizePixel(std::pair<int, int> size);
            void setSizeWindows(std::pair<int, int> size);
        
        private:
            std::map<sf::Keyboard::Key, Arcade::KeyState> _keyMap;
            std::map<sf::Keyboard::Key, bool> _keyInit;
            std::map<std::string, sf::Font> _fonts;
            std::map<std::string, sf::Texture> _sprites;

            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;

            bool _open;
    };
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create()
    {
        return (std::make_shared<Libs::SFML>());
    }
}

#endif /* !SFML_HPP_ */
