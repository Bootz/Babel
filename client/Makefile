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

OS 		= $(shell uname -s || echo Win32)

INCLUDES	= -I./hpp/ -I./../common/hpp/

DIR		= ./src/
SRC		= $(DIR)main.cpp		\
		  $(DIR)BabelClient.cpp

ifeq ($(OS), Win32)
	CPPFLAGS	= /EHsc $(INCLUDES)
	OBJ 		= $(SRC:.cpp:.obj)
	CC		= cl $(CPPFLAGS)
	RM		= del
else
	CPPFLAGS	= -W -Wall $(INCLUDES)
	OBJ		= $(SRC:.cpp=.o)
	CC		= g++
	RM		= rm -rf
endif

$(NAME)	: $(OBJ)
	$(CC) $(SRC) $(INCLUDES) -o $(NAME)

all	: $(NAME)

clean	:
ifeq ($(OS), Win32)
	$(RM) *.obj
else
	$(RM) $(OBJ)
endif

fclean	: clean
ifeq ($(OS), Win32)
	$(RM) $(NAME).exe
else
	$(RM) $(NAME)
endif

re	: fclean all

.PHONY	: all clean fclean re