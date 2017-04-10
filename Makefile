##
## Makefile for  in /home/le-rou_c/cpp/cparser
## 
## Made by Lucien Le Roux
## Login   <le-rou_c@epitech.net>
## 
## Started on  Sat Apr  8 11:39:59 2017 Lucien Le Roux
## Last update Sat Apr  8 14:16:54 2017 Lucien Le Roux
##

BIN		=	cparser

SRC		=	main.cpp	\
			CParser.cpp

OBJ		=	$(SRC:.cpp=.o)

RM		=	rm -f
CC		=	g++
# Compilation in c++03 is faster than 11
CPPFLAGS	=	-Wall -W --std=c++03

all:	$(BIN)

$(BIN):	$(OBJ)
	$(CC) $(CPPFLAGS) $(SRC) -o $@

clean:
	$(RM) $(OBJ)
fclean:	clean
	$(RM) $(EXE)
re:	fclean all
