##
## EPITECH PROJECT, 2022
## arcade
## File description:
## pacman
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard ../*.cpp)

OBJS		= $(SRC:.cpp=.o)
LIB 		= ../../../lib/arcade_pacman.so
LDFLAGS 	= -shared
CPPFLAGS	= -fPIC

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) $(CPPFLAGS) -o $@ $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIB)

re:	fclean all
