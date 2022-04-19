/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Core
*/

#include "Core.hpp"

Arcade::Core::Core()
{
    this->_releaseKey = false;

    this->_menuButton = 0;
    this->_menuGame = 0;
    this->_menuGraphic = 0;

    this->_currentGame = nullptr;
    this->_currentGraphic = nullptr;

    this->_loopRunning = false;
    this->_clock = std::make_shared<Pclock>(Pclock(REFRESH_TIME));
}

Arcade::Core::~Core()
{

}

void Arcade::Core::updateLib()
{
    std::pair<std::string, std::shared_ptr<Libs::IDisplayModule> > graphic;
    std::pair<int, int> SizeWindow;

    graphic = this->_graphics.getCurrent();
    SizeWindow = this->_currentGame->getSizeWindow();

    this->_currentGraphic->close();
    this->_currentGraphic = graphic.second.get();
    this->_currentGraphic->init(graphic.first, SizeWindow.first, SizeWindow.second);
    this->_currentGraphic->setSizePixel(this->_currentGame->getSizePixel());
    this->_currentGraphic->setSizeWindows(this->_currentGame->getSizeWindow());
}

void Arcade::Core::updateGame()
{
    this->_currentGame = this->_games.getCurrent().second.get();
    this->_currentGraphic->setSizeWindows(this->_currentGame->getSizeWindow());
}

void Arcade::Core::CoreLoop()
{
    std::string windowName = this->_graphics.getCurrent().first;
    std::pair<int, int> SizeWindow = this->_currentGame->getSizeWindow();
    std::vector<Arcade::KeyEvent_t> keyEvents;

    this->_currentGraphic = this->_graphics.getCurrent().second.get();
    this->_currentGraphic->init(windowName, SizeWindow.first, SizeWindow.second);
    this->_currentGraphic->setSizePixel(this->_currentGame->getSizePixel());
    this->_currentGraphic->setSizeWindows(this->_currentGame->getSizeWindow());

    while (this->_currentGraphic->isOpen() && this->_loopRunning) {

        keyEvents = this->_currentGraphic->getEvents();
        this->eventListener(keyEvents);

        this->update();
    }
}

void Arcade::Core::eventListener(std::vector<Arcade::KeyEvent_t> keyEvents)
{
    this->_currentGame->handleEvents(keyEvents);

    for (std::size_t t = 0; t < keyEvents.size(); t++) {

        if (this->isGameMenu()) {
            this->menuListener(keyEvents.at(t));
            continue;
        }

        if (this->hasChangedLib(keyEvents.at(t).key))
            this->updateLib();

        if (this->hasChangedGame(keyEvents.at(t).key))
            this->updateGame();

        if (keyEvents.at(t).key == Arcade::KeyState::M)
            this->goToMenu();

        if (keyEvents.at(t).key == Arcade::KeyState::E)
            this->_loopRunning = false;
    }
}

void Arcade::Core::menuListener(Arcade::KeyEvent_t event)
{
    this->menuMirroring(event.key);

    if (event.key == Arcade::KeyState::Enter && this->_menuButton == 4)
        this->_loopRunning = false;

    if (event.key == Arcade::KeyState::Enter && this->_menuButton == 0) {
        this->_games.setIndex(this->_menuGame + 1);
        this->_graphics.setIndex(this->_menuGraphic);
        this->updateLib();
        this->updateGame();
    }
}

bool Arcade::Core::isGameMenu()
{
    std::string gameName = this->_games.getCurrent().first;

    return (gameName == "menu");
}

void Arcade::Core::update()
{
    this->_currentGame->update();

    if (!this->_clock.get()->check())
        return;
    std::unordered_map<std::string, Arcade::Rect_t> shapes = this->_currentGame->getShapes();
    std::unordered_map<std::string, Arcade::Sprites_t> sprites = this->_currentGame->getSprites();
    std::unordered_map<std::string, Arcade::Text_t> texts = this->_currentGame->getTexts();

    this->_currentGraphic->my_clear();
    this->_currentGraphic->draw(shapes, sprites, texts);
    this->_currentGraphic->display();
}

void Arcade::Core::goToMenu()
{
    this->_games.setIndex(0);
    this->updateGame();
}

void Arcade::Core::menuMirroringSelectors(Arcade::KeyState key)
{
    if (key == Arcade::KeyState::Right) {
        if (this->_menuButton == 2)
            this->_menuGame = (this->_menuGame + 1) % (this->_games.getArr().size() - 1);
        if (this->_menuButton == 3)
            this->_menuGraphic = (this->_menuGraphic + 1) % this->_graphics.getArr().size();
    }
    if (key == Arcade::KeyState::Left) {
        if (this->_menuButton == 2)
            this->_menuGame = (this->_menuGame - 1);
        if (this->_menuButton == 3)
            this->_menuGraphic = (this->_menuGraphic - 1);
    }
}

void Arcade::Core::menuMirroringButtons(KeyState key)
{
    if (key == Arcade::KeyState::Down)
        this->_menuButton = (this->_menuButton + 1) % 5;
    if (key == Arcade::KeyState::Up)
        this->_menuButton = (this->_menuButton - 1) % 5;
    if (this->_menuButton < 0)
        this->_menuButton = 4;
}

void Arcade::Core::menuMirroring(Arcade::KeyState key)
{
    this->menuMirroringButtons(key);
    this->menuMirroringSelectors(key);

    if (this->_menuGame < 0)
        this->_menuGame = this->_games.getArr().size() - 2;
    if (this->_menuGraphic < 0)
        this->_menuGraphic = this->_graphics.getArr().size() - 1;
}

bool Arcade::Core::hasChangedGame(Arcade::KeyState key)
{
    bool ret = false;

    switch (key)
    {
    case Arcade::KeyState::Q:
        this->_games.previous();
        if (this->isGameMenu())
            this->_games.previous();
        ret = true;
        break;
    case Arcade::KeyState::S:
        this->_games.next();
        if (this->isGameMenu())
            this->_games.next();
        ret = true;
        break;
    default:
        break;
    }
    return (ret);
}

bool Arcade::Core::hasChangedLib(Arcade::KeyState key)
{
    bool ret = false;

    switch (key)
    {
    case Arcade::KeyState::A :
        this->_graphics.previous();
        ret = true;
        break;
    case KeyState::Z :
        this->_graphics.next();
        ret = true;
        break;
    default:
        break;
    }
    return (ret);
}

void Arcade::Core::init()
{
    this->loadGames();
    this->loadGraphics();
    this->_loopRunning = true;
}

void Arcade::Core::loadGames()
{
    this->_gamesAvailable.fill();
    for (const auto it: this->_gamesAvailable.getData())
        this->_games.addElement(it.first, this->_loader.getPtrFromObject<Games::IGameModule>(it.second, "create"));

    if (this->_games.getArr().size() < 2)
        throw (CoreError("Missing game", "Invalid init"));

    if (this->_games.getArr().at(0).first != "menu")
        throw (CoreError("Missing the menu", "Invalid init"));

    this->_currentGame = this->_games.getCurrent().second.get();
}

void Arcade::Core::loadGraphics()
{
    this->_graphicsAvailable.fill();
    for (const auto it: this->_graphicsAvailable.getData())
        this->_graphics.addElement(it.first, this->_loader.getPtrFromObject<Libs::IDisplayModule>(it.second, "create"));

    if (this->_graphics.getArr().size() == 0)
        throw (CoreError("Missing graphical library", "Invalid init"));

    this->_currentGraphic = this->_graphics.getCurrent().second.get();
}

Arcade::DLLoader Arcade::Core::getLoader() const
{
    return (this->_loader);
}

void Arcade::Core::initGraphics(std::string name)
{
    std::regex reg("lib\\/[^\\\\]+(\\.so$)");
    std::smatch match;
    std::regex_search(name, match, reg);
    bool validName = false;
    int index = 0;

    if (match[0] == "")
        throw (DlSelector("Invalid graphics library name", "Invalid library"));

    name = match[0];
    for (const auto it: this->_graphicsAvailable.getData()) {
        if (name == it.second) {
            this->_graphics.setIndex(index);
            validName = true;
        }
        index++;
    }

    if (validName == false)
        throw (DlSelector("Invalid graphics library", "Invalid library"));

    this->_currentGraphic = this->_graphics.getCurrent().second.get();
}
