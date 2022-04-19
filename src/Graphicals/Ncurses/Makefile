##
## EPITECH PROJECT, 2022
## arcade
## File description:
## ncurses
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard ../*.cpp)

OBJS		= $(SRC:.cpp=.o)
LIB 		= ../../../lib/arcade_ncurses.so
LDFLAGS 	= -shared
CPPFLAGS	= -fPIC -fno-gnu-unique

NCURSEFLAGS = -lncurses

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) $(CPPFLAGS) -o $@ $(OBJS) $(NCURSEFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIB)

re:	fclean all
