##
## Makefile for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
## 
## Made by koeth_y
## Login   <koeth_y@epitech.net>
## 
## Started on  Thu Nov 24 13:03:07 2011 koeth_y
## Last update Fri Dec  2 18:49:59 2011 koeth_y
##

CXX		= g++

LIB		= ../../lib/

INCLUDES	= -I../../hpp -I$(LIB)

CXXFLAGS	+= -W -Wall -Wextra $(INCLUDES)

ifdef DEBUG
	CXXFLAGS += -g3
else
	CXXFLAGS += -s -O3
endif

ARCHI		= $(shell uname -s)

LDFLAGS		+= -pthread -lportaudio -L$(LIB)$(ARCHI)

TEST1		= audioIO-test1
TEST2		= audioIO-test2

DIR		= ../../src/

COMMON_SOURCES =  $(DIR)IAudioIO.cpp		\
		  $(DIR)AudioData.cpp		\
		  $(DIR)PortAudio.cpp		\
		  $(DIR)IThread.cpp		\
		  $(DIR)UThread.cpp

TEST1_SOURCES 	= $(COMMON_SOURCES) test1.cpp
TEST2_SOURCES 	= $(COMMON_SOURCES) test2.cpp

TEST1_OBJECTS 	= $(TEST1_SOURCES:.cpp=.o)
TEST2_OBJECTS 	= $(TEST2_SOURCES:.cpp=.o)

RM 		= rm -f


all 	: $(TEST1) $(TEST2)

$(TEST1) : $(TEST1_OBJECTS)
	$(CXX) -o $(TEST1) $(TEST1_OBJECTS) $(LDFLAGS)

$(TEST2) : $(TEST2_OBJECTS)
	$(CXX) -o $(TEST2) $(TEST2_OBJECTS) $(LDFLAGS)

clean 	:
	$(RM) $(TEST1_OBJECTS)
	$(RM) $(TEST2_OBJECTS)

fclean 	: clean
	$(RM) $(TEST1)
	$(RM) $(TEST2)

re 	: fclean all

.PHONY	: all clean fclean re
