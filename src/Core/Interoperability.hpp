/*
** EPITECH PROJECT, 2022
** B-OOP-400-MPL-4-1-arcade-bastien.boymond
** File description:
** Interoperability
*/

#ifndef __INTEROPERABILITY_HPP__
    #define __INTEROPERABILITY_HPP__

    #include <string>

namespace Arcade {
    typedef struct Color_s {
        int r, g, b, a;
    } Color_t;

    typedef struct Rect_s {
        int x, y, w, h;
        Color_t bg;
        size_t layer;
    } Rect_t;

    typedef struct SpriteRect_s {
        int x, y, w, h;
        int maxW, maxH;
    } SpriteRect_t;

    typedef struct Sprites_s {
        int x, y;
        std::string path;
        SpriteRect_t rect;
        Color_t text;
        Color_t bg;
        size_t layer;
    } Sprites_t;

    typedef struct Text_s {
        std::string text;
        int x, y;
        Color_t colorText;
        unsigned int size;
        std::string font;
        size_t layer;
    } Text_t;

    enum KeyState {
        Unknown = -1,
        MouseClick,
        Left,
        Right,
        Up,
        Down,
        Enter,
        Escape,
        Return,
        Space,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
    };

    typedef struct KeyEvent_s {
        int x;
        int y;
        KeyState key;
    } KeyEvent_t;
};

#endif /* !INTEROPERABILITY_HPP */