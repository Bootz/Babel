##
## Makefile for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
## 
## Made by koeth_y
## Login   <koeth_y@epitech.net>
## 
## Started on  Thu Nov 24 13:03:07 2011 koeth_y
## Last update Thu Nov 24 13:12:02 2011 koeth_y
##

CXX		= g++
CXXFLAGS	+= -W -Wall -I../../hpp

LDFLAGS		+= -lportaudio -L../../lib

NAME		= audioIO-test

SOURCES 	= main.cpp			\
		  ../../src/AudioIO.cpp

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
