# Arcade

## About

Virtual arcade machine with a modudable code structure, the kernel is thus separated from the games and the graphic libraries.

## Screenshots

**Menu - SDL2**
![menu_sdl2](./img/menu_sdl2.png)

**Pacman - SFML**
![pacman_sfml](./img/pacman_sfml.png)

**Pacman - SDL2**
![pacman_sdl2](./img/pacman_sdl2.png)

**Pacman - Ncurses**
![pacman_ncurses](./img/pacman_ncurses.png)

**Nibbler - SFML**
![nibbler_sfml](./img/nibbler_sfml.png)

**Nibbler - Ncurses**
![nibler_sdl2](./img/nibbler_ncurses.png)

## How to build and run ?

1. Install the dependencies

**Debian / Ubuntu**
```bash
sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0 libsfml-dev libncurses5-dev libncursesw5-dev
```

**Arch Linux**
```bash
sudo pacman -Sy sdl2 sdl2_image sdl2_gfx sdl2_ttf sfml ncurses
```

2. Compile with `make`
3. Run the binary named `arcade`

## Contribute

To implement a graphic library or a game, you can read our documentation in `doc/`

## Authors

* **Théo Bori** - [github](https://github.com/theobori)
* **Antonin Ricard** - [github](https://github.com/antonin-11)
* **Martin Galtier**
  