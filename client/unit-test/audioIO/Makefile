##
## Makefile for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
## 
## Made by koeth_y
## Login   <koeth_y@epitech.net>
## 
## Started on  Thu Nov 24 13:03:07 2011 koeth_y
## Last update Tue Nov 29 16:06:52 2011 koeth_y
##

CXX		= g++

LIB		= ../../lib/

INCLUDES	= -I../../hpp -I$(LIB)

ifdef DEBUG
	CXXFLAGS += -W -Wall -Wextra -g3 $(INCLUDES)
else
	CXXFLAGS += -s -O3 $(INCLUDES)
endif

ARCHI		= `uname -s`

LDFLAGS		+= -pthread -lportaudio -L$(LIB)$(ARCHI)

NAME		= audioIO-test

DIR		= ../../src/

SOURCES 	= main.cpp			\
		  $(DIR)IAudioIO.cpp		\
		  $(DIR)AudioData.cpp		\
		  $(DIR)PortAudio.cpp

OBJECTS 	= $(SOURCES:.cpp=.o)

RM 		= rm -f


all 	: $(NAME)

$(NAME) : $(OBJECTS)
	$(CXX) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean 	:
	$(RM) $(OBJECTS)

fclean 	: clean
	$(RM) $(NAME)

re 	: fclean all

.PHONY	: all clean fclean re
