NAME		=	babel_server

SRCS		=	main.cpp \
			server.cpp \
			processingCore.cpp \
			clientManager.cpp \
			serverClient.cpp \
			lSocket.cpp

OBJS		=	$(SRCS:.cpp=.o)

TRASH		=	$(OBJS) \
			*.~

CC		=	g++

CFLAGS		=	-W -Wall -Wextra

RM		=	rm -f

all :	$(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
	$(RM) $(TRASH)

fclean :
	$(RM) $(NAME)
	$(RM) $(TRASH)

re : clean all
