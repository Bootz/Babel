##
## Makefile for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/thread
## 
## Made by koeth_y
## Login   <koeth_y@epitech.net>
## 
## Started on  Fri Dec  2 12:52:33 2011 koeth_y
## Last update Fri Dec  2 12:56:51 2011 koeth_y
##

CXX		= g++

INCLUDES	= -I../../hpp

CXXFLAGS	+= -W -Wall -Wextra $(INCLUDES)

ifdef DEBUG
	CXXFLAGS += -g3
else
	CXXFLAGS += -s -O3
endif

ARCHI		= $(shell uname -s)

LDFLAGS		+= -pthread

NAME		= thread-test

DIR		= ../../src/

SOURCES 	= main.cpp			\
		  $(DIR)IThread.cpp		\
		  $(DIR)UThread.cpp

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
