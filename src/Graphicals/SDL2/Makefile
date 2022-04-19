##
## EPITECH PROJECT, 2022
## arcade
## File description:
## SDL2
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard ../*.cpp)

OBJS		= $(SRC:.cpp=.o)
LIB 		= ../../../lib/arcade_sdl2.so
LDFLAGS 	= -shared
CPPFLAGS 	= -fno-gnu-unique -fPIC 
SDLFLAGS 	= -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@ $(CPPFLAGS) $(SDLFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIB)

re:	fclean all
