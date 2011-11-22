##
## Makefile for my_irc in /home/gelin_g/irc/src/client
## 
## Made by guillaume gelin
## Login   <gelin_g@epitech.net>
## 
## Started on  Fri Apr 22 12:31:53 2011 guillaume gelin
## Last update Tue Nov 22 19:26:02 2011 ramnes
##

NAME		= babel

DIR		= ./src/
SRC		= $(DIR)BabelClient.cpp

INCLUDES	= -I./hpp/
CPPFLAGS	= -W -Wall $(INCLUDES)
OBJ		= $(SRC:.cpp=.o)
CC		= g++
RM		= rm -rf

ifdef DEBUG
	CPPFLAGS += -g -ggdb3
else
	CPPFLAGS += -Werror -O3 -ffast-math
endif

$(NAME)	: $(OBJ)
	$(CC) $(SRC) $(INCLUDES) -o $(NAME)

all	: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all
