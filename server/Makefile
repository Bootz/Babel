##
## Makefile for Babel project
## 
## Made by ramnes
## <perso@ramnes.eu>
## 
## Started on  Thu Dec  1 18:02:20 2011 by ramnes
## Last update Sun Dec  4 18:26:21 2011 guillaume gelin
##

NAME		= babelserver

OS 		= $(shell uname -s || echo Win32)

DIR		= ./src/

COMMON		= ../common/src/

INCLUDES	= -I./hpp/ -I./../common/hpp/

SRC		= 	$(DIR)main.cpp \
			$(DIR)Server.cpp \
			$(DIR)ProcessingCore.cpp \
			$(DIR)ClientManager.cpp \
			$(DIR)ServerClient.cpp \
			$(COMMON)Socket_$(OS).cpp \
			$(COMMON)BabelProtocol.cpp

ifdef DEBUG
	CPPFLAGS = -g -ggdb3
else
	CPPFLAGS = -Werror -O3 -ffast-math
endif

ifeq ($(OS), Win32)
	CPPFLAGS	= /EHsc $(INCLUDES)
	OBJ 		= $(SRC:.cpp:.obj)
	CC		= cl $(CPPFLAGS)
	RM		= del
else
	CPPFLAGS	+= -W -Wall $(INCLUDES)
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
