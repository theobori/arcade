##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

NCURSES_DIR = Ncurses
SDL2_DIR = SDL2
SFML_DIR = SFML

all: ncurses sdl sfml

ncurses:
	$(MAKE) -C $(NCURSES_DIR)

sdl:
	$(MAKE) -C $(SDL2_DIR)

sfml:
	$(MAKE) -C $(SFML_DIR)

clean:
	$(MAKE) -C $(NCURSES_DIR) clean
	$(MAKE) -C $(SDL2_DIR) clean
	$(MAKE) -C $(SFML_DIR) clean

fclean: clean
	$(MAKE) -C $(NCURSES_DIR) fclean
	$(MAKE) -C $(SDL2_DIR) fclean
	$(MAKE) -C $(SFML_DIR) fclean

re:
	$(MAKE) -C $(NCURSES_DIR) re
	$(MAKE) -C $(SDL2_DIR) re
	$(MAKE) -C $(SFML_DIR) re