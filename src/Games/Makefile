##
## EPITECH PROJECT, 2021
## arcade
## File description:
## Makefile
##

NIBBLER_DIR = Nibbler
PACMAN_DIR = Pacman
MENU_DIR = Menu

CURENT = ./

SRC			= 	$(wildcard *.cpp)
OBJ			= 	$(SRC:.cpp=.o)
CPPFLAGS		= 	-W -Wall -Wextra

all: pacman nibbler menu $(OBJ)

nibbler:
	$(MAKE) -C $(NIBBLER_DIR)

pacman:
	$(MAKE) -C $(PACMAN_DIR)

menu:
	$(MAKE) -C $(MENU_DIR)

clean:	
	$(RM) *~
	$(RM) #*#
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) $(OBJ)
	$(MAKE) -C $(NIBBLER_DIR) clean
	$(MAKE) -C $(PACMAN_DIR) clean
	$(MAKE) -C $(MENU_DIR) clean

fclean: clean
	$(MAKE) -C $(NIBBLER_DIR) fclean
	$(MAKE) -C $(PACMAN_DIR) fclean
	$(MAKE) -C $(MENU_DIR) fclean

re:
	$(MAKE) -C $(NIBBLER_DIR) re
	$(MAKE) -C $(PACMAN_DIR) re
	$(MAKE) -C $(MENU_DIR) re
