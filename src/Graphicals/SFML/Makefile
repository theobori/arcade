##
## EPITECH PROJECT, 2022
## arcade
## File description:
## SFML
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard ../*.cpp)

OBJS		= $(SRC:.cpp=.o)
LIB 		= ../../../lib/arcade_sfml.so
LDFLAGS 	= -shared
CPPFLAGS	= -fPIC -fno-gnu-unique
SFMLDLAGS	= -lsfml-graphics -lsfml-window -lsfml-system

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(CPPFLAGS) $(SFMLDLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIB)

re:	fclean all
