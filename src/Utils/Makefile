##
## EPITECH PROJECT, 2022
## arcade
## File description:
## utils
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard Available/*.cpp)
CPPFLAGS	= -fPIC

OBJS		= $(SRC:.cpp=.o)

all: build

build: $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIB)

re:	fclean all
