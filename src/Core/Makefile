##
## EPITECH PROJECT, 2020
## arcade
## File description:
## Core
##

CC	= g++

SRC			= 	$(wildcard *.cpp)
SRC			+= 	$(wildcard ../Utils/Available/*.cpp)

OBJ			= 	$(SRC:.cpp=.o)
BIN 		= 	../../arcade
CPPFLAGS	= 	-W -Wall -Wextra -fno-gnu-unique
COREFLAGS 	=	-ldl

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CPPFLAGS) $(COREFLAGS)

clean:
	$(RM) *~
	$(RM) #*#
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) $(OBJ)

fclean: clean
	$(RM) test
	$(RM) $(BIN)

re: fclean all
