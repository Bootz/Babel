##
## Makefile for my_irc in /home/gelin_g/irc/src/client
## 
## Made by guillaume gelin
## Login   <gelin_g@epitech.net>
## 
## Started on  Fri Apr 22 12:31:53 2011 guillaume gelin
## Last update Thu Dec  1 19:39:31 2011 ramnes
##

NAME		= test

OS 		= $(shell uname -s || echo Win32)

DIR		= ./
SRC		= $(DIR)Test_$(OS).cpp

INCLUDES	= -I./hpp/ -I./../common/hpp/

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