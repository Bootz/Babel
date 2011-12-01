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

DIR		= ./src/

COMMON		= ../common/src/

SRC		= 	$(DIR)main.cpp \
			$(DIR)Server.cpp \
			$(DIR)ProcessingCore.cpp \
			$(DIR)ClientManager.cpp \
			$(DIR)ServerClient.cpp \
			$(DIR)LSocket.cpp \
			$(DIR)Factory.cpp \
			$(COMMON)BabelProtocol.cpp


INCLUDES	= -I./hpp/ -I./../common/hpp/
CPPFLAGS	= -W -Wall $(INCLUDES)
OBJ		= $(SRC:.cpp=.o)
CC		= g++
RM		= rm -rf

DEBUG		= 0

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
