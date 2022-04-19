##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

CORE_DIR = src/Core
GAMES_DIR = ./src/Games
GRAPHICALS_DIR = src/Graphicals
UTILS_DIR = src/Utils

all: utils graphicals games core

core:
	$(MAKE) -C $(CORE_DIR)

games:
	$(MAKE) -C $(GAMES_DIR)

graphicals:
	$(MAKE) -C $(GRAPHICALS_DIR)

utils:
	$(MAKE) -C $(UTILS_DIR)

clean:
	$(MAKE) -C $(CORE_DIR) clean
	$(MAKE) -C $(GAMES_DIR) clean
	$(MAKE) -C $(GRAPHICALS_DIR) clean
	$(MAKE) -C $(UTILS_DIR) clean

fclean: clean
	$(MAKE) -C $(CORE_DIR) fclean
	$(MAKE) -C $(GAMES_DIR) fclean
	$(MAKE) -C $(GRAPHICALS_DIR) fclean
	$(MAKE) -C $(UTILS_DIR) fclean

re: fclean
	$(MAKE) -C $(CORE_DIR) re
	$(MAKE) -C $(GAMES_DIR) re
	$(MAKE) -C $(GRAPHICALS_DIR) re
	$(MAKE) -C $(UTILS_DIR) re