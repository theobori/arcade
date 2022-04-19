##
## EPITECH PROJECT, 2022
## arcade
## File description:
## nibbler
##

CC			= g++

SRC 		= $(wildcard *.cpp)
SRC 		+= $(wildcard Button/*.cpp)
SRC 		+= $(wildcard ../*.cpp)
SRC 		+= $(wildcard ../../Utils/Available/*.cpp)

OBJS		= $(SRC:.cpp=.o)
LIB 		= ../../../lib/arcade_menu.so
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
