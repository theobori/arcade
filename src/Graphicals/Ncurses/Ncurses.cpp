/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Libs::Ncurses::Ncurses()
{
    this->_open = true;
    this->_sprites = {};
    this->_keyMap = {
        {0, Arcade::KeyState::Unknown},
        {KEY_LEFT, Arcade::KeyState::Left},
        {KEY_RIGHT, Arcade::KeyState::Right},
        {KEY_UP, Arcade::KeyState::Up},
        {KEY_DOWN, Arcade::KeyState::Down},
        {10, Arcade::KeyState::Enter},
        {27, Arcade::KeyState::Escape},
        {KEY_BACKSPACE, Arcade::KeyState::Return},
        {97, Arcade::KeyState::A},
        {98, Arcade::KeyState::B},
        {99, Arcade::KeyState::C},
        {100, Arcade::KeyState::D},
        {101, Arcade::KeyState::E},
        {102, Arcade::KeyState::F},
        {103, Arcade::KeyState::G},
        {104, Arcade::KeyState::H},
        {105, Arcade::KeyState::I},
        {106, Arcade::KeyState::J},
        {107, Arcade::KeyState::K},
        {108, Arcade::KeyState::L},
        {109, Arcade::KeyState::M},
        {110, Arcade::KeyState::N},
        {111, Arcade::KeyState::O},
        {112, Arcade::KeyState::P},
        {113, Arcade::KeyState::Q},
        {114, Arcade::KeyState::R},
        {115, Arcade::KeyState::S},
        {116, Arcade::KeyState::T},
        {117, Arcade::KeyState::U},
        {118, Arcade::KeyState::V},
        {119, Arcade::KeyState::W},
        {120, Arcade::KeyState::X},
        {121, Arcade::KeyState::Y},
        {122, Arcade::KeyState::Z}
    };
    this->_pixelSize = {-1, -1};
}

void Libs::Ncurses::init_pair_color()
{
    for (int f = 0; f < 8; f++) {
        for (int b = 0; b < 8; b++) {
            init_pair((f * 10) + b, f, b);
        }
    }
}

int Libs::Ncurses::rbg_to_color(int r, int g, int b)
{
    int closerValue = 255 * 3 + 1;
    int closer = 0;
    int diff = 0;
    std::vector<int> rgb = {0, 0, 0};

    for (int t = 0; t < 8; t++) {
        rgb = this->color[t];
        diff = 0;
        diff += std::abs(rgb.at(0) - r);
        diff += std::abs(rgb.at(1) - g);
        diff += std::abs(rgb.at(2) - b);
        if (diff < closerValue) {
            closer = t;
            closerValue = diff;
        }
    }
    return (closer);
}

Libs::Ncurses::~Ncurses()
{
    endwin();
}

void Libs::Ncurses::init(std::string name, int w, int h)
{
    this->_window = initscr();
    start_color();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    nodelay(stdscr, TRUE);
    clear();
    refresh();
    cbreak();
    this->height = h / this->_pixelSize.second;
    this->width = w / this->_pixelSize.first;
    this->init_pair_color();
    this->color = {
        {0, {0, 0, 0}},
        {1, {255, 0, 0}},
        {2, {0, 255, 0}},
        {3, {255, 255, 0}},
        {4, {0, 0, 255}},
        {5, {255, 0, 255}},
        {6, {0, 255, 255}},
        {7, {255, 255, 255}}
    };
}

void Libs::Ncurses::my_print(int y, int x, std::string filename, int ft, int bg)
{
    attron(COLOR_PAIR((ft * 10) + bg));
    mvprintw(y + ((LINES - this->height) / 2), x + ((COLS - this->width) / 2), filename.c_str());
    attroff(COLOR_PAIR((ft * 10) + bg));
}

std::vector<Arcade::KeyEvent_t> Libs::Ncurses::getEvents()
{
    std::vector<Arcade::KeyEvent_t> ret;
    Arcade::KeyEvent_t tmp;
    int NKey = 0;

    tmp.key = Arcade::KeyState::Unknown;
    tmp.x = 0;
    tmp.y = 0;

    while ((NKey = getch()) != ERR) {
        MEVENT event;
        if (NKey == KEY_MOUSE && getmouse(&event) == OK) {
            tmp.y = event.y;
            tmp.x = event.x;
        }
        tmp.key = this->_keyMap[NKey];
        ret.push_back(tmp);
    }
    return (ret);
}

bool Libs::Ncurses::isOpen() const
{
    return (this->_open);
}

void Libs::Ncurses::close()
{
    endwin();
}

bool Libs::Ncurses::drawShapes(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
    int myHeight = 0;
    int myWidth = 0;
    int bg = 0;
    int ft = 0;
    bool ret = false;

    for (auto& it: shapes) {
        Arcade::Rect_t rect = it.second;

        if (rect.layer != layer)
            continue;
        
        ret = true;
        myHeight = (rect.h / this->_pixelSize.second);
        myWidth = (rect.w / this->_pixelSize.first);
        myHeight = (myHeight == 0) ? 1 : myHeight;
        myWidth = (myWidth == 0) ? 1 : myWidth;
        for (int h = 0; h < myHeight; h++) {
            for (int w = 0; w < myWidth; w++) {
                bg = rbg_to_color(rect.bg.r, rect.bg.g, rect.bg.b);
                my_print((rect.y / this->_pixelSize.second) + h, (rect.x / this->_pixelSize.first) + w, " ", 7, bg);
            }
        }
    }

    return(ret);
}

bool Libs::Ncurses::drawSprites(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
    int line = 0;
    bool ret = false;
    int fgColor = 0;
    int bgColor = 0;

    for (auto& it: sprites) {
        line = 0;
        Arcade::Sprites_t sprite = it.second;

        if (sprite.layer != layer)
            continue;

        ret = true;
        std::string file = this->my_get_file(sprite.path + ".txt");
        std::vector<std::string> formatFile = this->splitString(file, "\n");

        for (auto& value: formatFile) {

            if (sprite.text.r != -1 || sprite.text.g != - 1 || sprite.text.b != -1 || sprite.text.a != -1)
                fgColor = rbg_to_color(sprite.text.r, sprite.text.g, sprite.text.b);
            else
                fgColor = 7;
            if (sprite.bg.r != -1 || sprite.bg.g != - 1 || sprite.bg.b != -1 || sprite.bg.a != -1)
                bgColor = rbg_to_color(sprite.bg.r, sprite.bg.g, sprite.bg.b);
            else
                bgColor = 0;
    
            my_print((sprite.y / this->_pixelSize.second) + line, sprite.x / this->_pixelSize.first, value.c_str(), fgColor, bgColor);
            line++;
        }
    }

    return (ret);
}

bool Libs::Ncurses::drawTexts(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
    int bg = 0;
    int ft = 0;
    bool ret = false;

    for (auto& it: texts) {
        Arcade::Text_t text = it.second;

        if (text.layer != layer)
            continue;
        
        ret = true;
        ft = this->rbg_to_color(text.colorText.r, text.colorText.g, text.colorText.b);
        my_print((text.y / this->_pixelSize.second), (text.x / this->_pixelSize.first), text.text.c_str(), ft, bg);
    }
    return (ret);
}

void Libs::Ncurses::my_clear() const 
{
    erase();
}

void Libs::Ncurses::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
{
    size_t layer = 0;
    bool draw = true;

    this->my_clear();
    while (draw == true) {
        draw = false;
        draw |= this->drawShapes(shapes, layer);
        draw |= this->drawSprites(sprites, layer);
        draw |= this->drawTexts(texts, layer);
        layer++;
    }
}

void Libs::Ncurses::display() const
{
    refresh();
}

std::string Libs::Ncurses::my_get_file(std::string filename)
{
    std::string contentFile;
    std::stringstream sstr;
    std::ifstream f(filename, std::ios::in);

    if (this->_sprites.count(filename))
        return (this->_sprites[filename]);

    if (f.is_open() == false)
        throw NcursesError("Unable to open the file", "Invalid Window");

    sstr << f.rdbuf();
    contentFile = sstr.str();
    f.close();
    this->_sprites[filename] = contentFile;
    return (contentFile);
}

std::vector<std::string> Libs::Ncurses::splitString(std::string str, std::string delimiter)
{
    std::string s = str;
    std::vector<std::string> list;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return (list);
}

void Libs::Ncurses::setSizePixel(std::pair<int, int> size)
{
    this->_pixelSize = size;
}

void Libs::Ncurses::setSizeWindows(std::pair<int, int> size)
{
    this->height = size.second / this->_pixelSize.second;
    this->width = size.first / this->_pixelSize.first;
}