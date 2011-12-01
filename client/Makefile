##
## Makefile for Babel project
## 
## Made by ramnes
## <perso@ramnes.eu>
## 
## Started on  Thu Dec  1 18:01:53 2011 by ramnes
## Last update Thu Dec  1 18:01:54 2011 ramnes
##

NAME		= babel

DIR		= ./src/
SRC		= $(DIR)main.cpp		\
		  $(DIR)BabelClient.cpp

INCLUDES	= -I./hpp/ -I./../common/hpp/
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

.PHONY	: all clean fclean re