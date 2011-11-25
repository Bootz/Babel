##
## Makefile for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
## 
## Made by koeth_y
## Login   <koeth_y@epitech.net>
## 
## Started on  Thu Nov 24 13:03:07 2011 koeth_y
## Last update Fri Nov 25 13:16:53 2011 koeth_y
##

CXX		= g++

CXXFLAGS	+= -W -Wall -I../../hpp -I../../lib -g3

ARCHI		= `uname -s`

LDFLAGS		+= -pthread -lportaudio -L../../lib/$(ARCHI)

NAME		= audioIO-test

SOURCES 	= main.cpp			\
		  ../../src/IAudioIO.cpp	\
		  ../../src/AudioData.cpp	\
		  ../../src/PortAudio.cpp

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
