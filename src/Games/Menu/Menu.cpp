/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Menu
*/

#include "Menu.hpp"

Games::Menu::Menu()
{
    this->_sprites = {};
    this->_shapes = {};
    this->_texts = {};
    this->_highScore = "";

    this->_functions = {
        {Arcade::KeyState::Down, KEY_FUNC_CTOR(nextButton)},
        {Arcade::KeyState::Up, KEY_FUNC_CTOR(previousButton)},
        {Arcade::KeyState::Left, KEY_FUNC_CTOR(previousSelector)},
        {Arcade::KeyState::Right, KEY_FUNC_CTOR(nextSelector)},
        {Arcade::KeyState::Enter, KEY_FUNC_CTOR(play)}
    };

    this->_keyToString = {
        {Arcade::KeyState::A, "A"},
        {Arcade::KeyState::B, "B"},
        {Arcade::KeyState::C, "C"},
        {Arcade::KeyState::D, "D"},
        {Arcade::KeyState::E, "E"},
        {Arcade::KeyState::F, "F"},
        {Arcade::KeyState::G, "G"},
        {Arcade::KeyState::H, "H"},
        {Arcade::KeyState::I, "I"},
        {Arcade::KeyState::J, "J"},
        {Arcade::KeyState::K, "K"},
        {Arcade::KeyState::L, "L"},
        {Arcade::KeyState::M, "M"},
        {Arcade::KeyState::N, "N"},
        {Arcade::KeyState::O, "O"},
        {Arcade::KeyState::P, "P"},
        {Arcade::KeyState::Q, "Q"},
        {Arcade::KeyState::R, "R"},
        {Arcade::KeyState::S, "S"},
        {Arcade::KeyState::T, "T"},
        {Arcade::KeyState::U, "U"},
        {Arcade::KeyState::V, "V"},
        {Arcade::KeyState::W, "W"},
        {Arcade::KeyState::X, "X"},
        {Arcade::KeyState::Y, "Y"},
        {Arcade::KeyState::Z, "Z"}
    };

    this->init();
}

Games::Menu::~Menu()
{
    Games::IButton *button = NULL;
}

void Games::Menu::init()
{
    this->initButtons();
    this->refreshScoresData();
    this->_logo = {
        this->wCenter(544), 10,
        "./assets/menu/logo",
        {0, 0, 544, 96, 0, 0}, 
        {}, {}, 0
    };
    this->_cursorSelector = {
        0, 0,
        "./assets/menu/cursor_selector",
        {0, 0, 64, 64, 0, 0}, 
        {}, {}, 0
    };
    this->_cursorDefault = {
        0, 0,
        "./assets/menu/cursor_default",
        {0, 0, 64, 64, 0, 0}, 
        {}, {}, 0
    };
    this->_cursorInput = {
        0, 0,
        "./assets/menu/cursor_input",
        {0, 0, 64, 64, 0, 0}, 
        {}, {}, 0
    };
    this->_scores = {
        this->wCenter(160) + 230, this->hCenter(352),
        "./assets/menu/scores",
        {0, 0, 160, 352, 0, 0}, 
        {}, {}, 0
    };
}

void Games::Menu::setCursor()
{
    std::string buttonName = this->_buttons.getCurrent().first;
    int x = this->_sprites[buttonName].x - 70;
    int y = this->_sprites[buttonName].y;
    Games::IButton *button = this->_buttons.getCurrent().second;

    switch (button->getType())
    {
    case (Button::TYPE::GAME_SELECTOR):
    case (Button::TYPE::LIB_SELECTOR):
        this->_cursorSelector.x = x;
        this->_cursorSelector.y = y;
        this->_sprites["cursor_selector"] = this->_cursorSelector;
        break;        
    case (Button::TYPE::INPUT):
        this->_cursorInput.x = x;
        this->_cursorInput.y = y;
        this->_sprites["cursor_input"] = this->_cursorInput;
        break;
    default:
        this->_cursorDefault.x = x;
        this->_cursorDefault.y = y;
        this->_sprites["cursor_default"] = this->_cursorDefault;
        break;
    }
}

void Games::Menu::initButtons()
{
    int groupX = this->wCenter(384) - 90;
    Utils::Games gamesAvailable;
    Utils::Graphics graphicsAvailable;

    gamesAvailable.fill();
    graphicsAvailable.fill();

    // Selectors
    // Game selector
    this->_gameSelector = std::make_shared<GameSelector>(GameSelector({
        groupX, 330,
        "./assets/menu/button_selector",
        {0, 0, 384, 96, 0, 0},
        {}, {}, 0
    }));

    for (const auto it: gamesAvailable.getData()) {
        if (it.first == "menu")
            continue;
        this->_gameSelector.get()->getData().addElement(it.first, GameData("./assets/" + it.first + "/scores.txt"));
    }

    // Lib selector
    this->_libSelector = std::make_shared<LibSelector>(LibSelector({
        groupX, 440,
        "./assets/menu/button_selector",
        {0, 0, 384, 96, 0, 0},
        {}, {}, 0
    }));

    for (const auto it: graphicsAvailable.getData())
        this->_libSelector.get()->getData().addElement(it.first, it.first);

    this->_playButton = std::make_shared<OneClick>(OneClick({
        groupX, 110,
        "./assets/menu/button_play",
        {0, 0, 384, 96, 0, 0},
        {}, {}, 0
    }));

    this->_inputButton = std::make_shared<Input>(Input({
        groupX, 220,
        "./assets/menu/button_selector",
        {0, 0, 384, 96, 0, 0},
        {}, {}, 0
    }));

    this->_quitButton = std::make_shared<OneClick>(OneClick({
        groupX, 550,
        "./assets/menu/button_exit",
        {0, 0, 384, 96, 0, 0},
        {}, {}, 0
    }));

    // Group buttons
    this->_buttons.addElement("PlayButton", this->_playButton.get());
    this->_buttons.addElement("InputButton", this->_inputButton.get());
    this->_buttons.addElement("GameButton", this->_gameSelector.get());
    this->_buttons.addElement("LibButton", this->_libSelector.get());
    this->_buttons.addElement("QuitButton", this->_quitButton.get());
}

void Games::Menu::updateButtons()
{
    unsigned int i = 0;
    Arcade::Sprites_t sprite;
    Arcade::SpriteRect_t spriteRect;
    std::string data = "";

    for (auto &it : this->_buttons.getArr()) {

        if (this->_sprites.count(it.first) == 0) {
            sprite = it.second->getSprite();
            this->_sprites[it.first] = sprite;
        }
    
        data = it.second->getFormattedData();
        i++;
        if (data.size() == 0)
            continue;

        this->_texts[it.first + "desc"] = {
            data,
            sprite.x + this->wCenter(data.size() * 18, sprite.rect.w), 
            sprite.y + this->hCenter(30, sprite.rect.h),
            {42, 130, 255, 255}, 30,
            "./assets/fonts/liberation.ttf",
            0
        };
    }
}

void Games::Menu::refreshScoresData()
{
    Games::IButton *gameButton = this->_buttons.getByKey("GameButton");

    gameButton->refreshSelector();
    this->_lastScores = Games::GameData::split(gameButton->getDetails(), "\n");
    this->_highScore = gameButton->getBest();
}

void Games::Menu::updateScores()
{
    int i = 0;

    for (const auto it : this->_lastScores) {
        this->_texts[it + std::to_string(i)] = {
            it,
            this->wCenter(160) + 230 + 10,
            this->hCenter(343) + (13 * i) + 180,
            {42, 130, 255, 255}, 13,
            "./assets/fonts/liberation.ttf",
            0
        };
        i++;
    }

    this->_texts["bestSave"] = {
        this->_highScore,
        this->wCenter(160) + 230 + 10,
        this->hCenter(343) + 55,
        {255, 249, 42, 255}, 13,
        "./assets/fonts/liberation.ttf",
        0
    };
}

void Games::Menu::update()
{
    this->_sprites.clear();
    this->_texts.clear();
    this->_sprites["logo"] = this->_logo;
    this->_sprites["scores"] = this->_scores;
    this->refreshScoresData();
    this->updateScores();
    this->updateButtons();
    this->setCursor();
}

void Games::Menu::previousButton(Arcade::KeyEvent_t event)
{
    this->_buttons.previous();
}

void Games::Menu::nextButton(Arcade::KeyEvent_t event)
{
    this->_buttons.next();
}

void Games::Menu::previousSelector(Arcade::KeyEvent_t event)
{
    std::pair<std::string, Games::IButton *> pair = this->_buttons.getCurrent();
    std::string key = pair.first;
    Games::IButton *button = pair.second;

    switch (button->getType())
    {
    case (Button::TYPE::GAME_SELECTOR):
        dynamic_cast<Games::GameSelector *>(button)->getData().previous();
        break;
    case (Button::TYPE::LIB_SELECTOR):
        dynamic_cast<Games::LibSelector *>(button)->getData().previous();
        break;
    default:
        break;
    }
}

void Games::Menu::nextSelector(Arcade::KeyEvent_t event)
{
    std::pair<std::string, Games::IButton *> pair = this->_buttons.getCurrent();
    std::string key = pair.first;
    Games::IButton *button = pair.second;

    switch (button->getType())
    {
    case (Button::TYPE::GAME_SELECTOR):
        dynamic_cast<Games::GameSelector *>(button)->getData().next();
        break;
    case (Button::TYPE::LIB_SELECTOR):
        dynamic_cast<Games::LibSelector *>(button)->getData().next();
        break;
    default:
        break;
    }
}

void Games::Menu::play(Arcade::KeyEvent_t event)
{
    Games::IButton *input= this->_buttons.getByKey("InputButton");
    std::ofstream file;

    if (this->getButtonName() != "PlayButton")
        return;

    file.open("./assets/name.txt");
    file << input->getFormattedData();
    file.close();
}

std::unordered_map<std::string, Arcade::Rect_t> Games::Menu::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::Menu::getSprites()
{
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::Menu::getTexts()
{
    return (this->_texts);
}

std::pair<int, int> Games::Menu::getSizeWindow()
{
    return (std::pair<int, int>(1000, 650));
}

bool Games::Menu::typeInput(Arcade::KeyState key)
{
    Games::IButton *button = this->_buttons.getCurrent().second;

    if (button->getType() != IButton::TYPE::INPUT)
        return (false);
    if (key == Arcade::KeyState::Left) {
        button->removeString(1);
        return (true);
    }
    if (this->_keyToString.count(key) == 0)
        return (false);
    
    button->addString(this->_keyToString[key]);
    return (true);
}

void Games::Menu::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    for (const auto it : event) {
        if (typeInput(it.key) == true)
            break;
        if (this->_functions.count(it.key))
            this->_functions[it.key](this, it);
    }
}

std::string Games::Menu::getButtonName()
{
    return (this->_buttons.getCurrent().first);
}
