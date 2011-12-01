//
// Socket.cpp for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:30:07 2011 louis lesueur
// Last update Thu Dec  1 20:51:35 2011 louis lesueur
//

#include		<string.h>
#include		<cstring>
#include		"Exception.hpp"
#include		"LSocket.hpp"

LSocket::LSocket()
  : ListenSocket(-1),
    AcceptSocket(-1)
{
  this->SenderAddrSize = sizeof(this->SenderAddr);
  this->buffer = new char[this->SizeInterBuff];
}

LSocket::~LSocket()
{
  close(this->ListenSocket);
}

bool			LSocket::connectToServer(unsigned short port)
{
  struct sockaddr_in   addr;
  struct protoent*	pe;

  (void) addr;
  pe = getprotobyname("tcp");
  if ((this->ListenSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw BabelException("[UNIX] Error at socket()");
  if(setsockopt(this->ListenSocket, SOL_SOCKET, SO_REUSEADDR, &this->ListenSocket, sizeof(int)) == -1)
    throw BabelException("[UNIX] Error at socket()");
  memset(&this->sin, 0, sizeof(&this->sin));
  this->sin.sin_family = AF_INET;
  this->sin.sin_port = htons(port);
  this->sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->ListenSocket, (struct sockaddr *)&this->sin, sizeof(addr)) != 0)
    throw BabelException("[UNIX] Error at socket()");
  if (listen(this->ListenSocket, 1024) != 0)
    throw BabelException("[UNIX] Error at socket()");
  return (true);
}

void			LSocket::setAcceptSocket(SOCKET _sock)
{
  this->AcceptSocket = _sock;
}

SOCKET			LSocket::getListenSocket(void)const
{
  return (this->ListenSocket);
}

SOCKET			LSocket::getAcceptSocket(void)const
{
  return (this->AcceptSocket);
}

int			LSocket::send_d(SOCKET sock, std::string & str)
{
  int			nb_write = 0;
  int			tmp = 0;
  int			size = str.size();

  str.copy(this->buffer, 0, size);
  while (tmp != size)
    {
      nb_write = send(sock, (this->buffer + tmp), strlen((this->buffer + tmp)), 0);
      if (nb_write == -1)
	throw BabelException("[ERROR] send() operation failed");
      tmp += nb_write;
    }
  memset(this->buffer, 0, this->SizeInterBuff);
  return (nb_write);
}

int			LSocket::recv_d(SOCKET sock, std::string& str)
{
  int			nb_read = 0;
  int			nbr = 0;
  int			size = SizeInterBuff;
  int			flag = 1;

  while (flag)
    {
      nb_read = recv(sock, (this->buffer + nbr), SizeInterBuff - nbr, 0);
      nbr += nb_read;
      if (nb_read < 0)
	throw BabelException("[ERROR] recv() operation failed");
      if (nbr >= size || (nbr >= 1 && this->buffer[nbr-1] == '\n') ||
	  (nbr >= 2 && this->buffer[nbr-2] == '\n' && this->buffer[nbr-1] == '\r'))
	{
	  this->buffer[nbr] = '\0';
	  flag = 0;
	}
    }
  str = this->buffer;
  memset(this->buffer, 0, this->SizeInterBuff);
  return (nb_read);
}

int			LSocket::getSocket() const
{
  return (ListenSocket);
}

int			LSocket::clientAccept(int s)
{
  unsigned int		client_sin_len;
  struct sockaddr_in    client_sin;
  int			cs;

  client_sin_len = sizeof(client_sin);
  if ((cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len)) < 0)
    throw BabelException("[ERROR] accept() operation failed");
  std::cout << "[clientAccept] New client added" << std::endl;
  return (cs);
}

void			LSocket::closeSocket(void)
{
  close(this->ListenSocket);
}

struct sockaddr_in*	LSocket::getSin(void)
{
  return (&this->sin);
}
