##
## Makefile for Babel project
## 
## Made by ramnes
## <perso@ramnes.eu>
## 
## Started on  Thu Dec  1 18:02:20 2011 by ramnes
## Last update Thu Dec  1 18:02:58 2011 ramnes
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
			$(DIR)Socket_$(OS).cpp \
			$(DIR)Factory.cpp \
			$(COMMON)BabelProtocol.cpp

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
