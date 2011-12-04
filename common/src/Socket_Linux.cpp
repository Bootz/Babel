//
// Socket.cpp for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:30:07 2011 louis lesueur
// Last update Sun Dec  4 19:46:40 2011 louis lesueur
//

#include		<string.h>
#include		<cstring>
#include		"BabelException.hpp"
#include		"Socket_Linux.hpp"

LSocket::LSocket()
  : ListenSocket(-1),
    AcceptSocket(-1)
{
  this->SenderAddrSize = sizeof(this->SenderAddr);
}

LSocket::~LSocket()
{
  close(this->ListenSocket);
}

bool			LSocket::connectToServer(std::string const& host, unsigned short port)
{
  struct protoent*	pe;

  pe = getprotobyname("tcp");
  this->ListenSocket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (this->ListenSocket == -1)
    throw BabelException("[UNIX] Error at socket()");
  this->sin.sin_family = AF_INET;
  if (host != "INADDR_ANY")
    this->sin.sin_addr.s_addr = inet_addr(host.c_str());
  else
    this->sin.sin_addr.s_addr = INADDR_ANY;
  this->sin.sin_port = htons(port);
  return (true);
}

bool			LSocket::initServer(unsigned short port)
{
  struct sockaddr_in   addr;

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

int			LSocket::send_d(SOCKET sock, char *str)
{
  int			nb_write = 0;
  int			tmp = 0;
  int			size;

  if (str)
    size = strlen(str);
  else
    size = 0;
  while (tmp != size)
    {
      nb_write = send(sock, (str + tmp), strlen((str + tmp)), 0);
      if (nb_write == -1)
	throw std::exception();
      tmp += nb_write;
    }
  memset(str, 0, size);
  return (nb_write);
}

int			LSocket::recv_d(SOCKET sock, char *str)
{
  int			nb_read = 0;
  int			nbr = 0;
  int			size = SizeInterBuff;
  int			flag = 1;

  memset(str, 0, this->SizeInterBuff);
  while (flag)
    {
      nb_read = recv(sock, (str + nbr), SizeInterBuff - nbr, 0);
      nbr += nb_read;
      if (nb_read < 0)
	throw BabelException("[ERROR] recv() operation failed");
      if (nb_read == 0 || nbr >= size || (nbr >= 1 && str[nbr-1] == '\n') ||
	  (nbr >= 2 && str[nbr-2] == '\n' && str[nbr-1] == '\r'))
	{
	  str[nbr] = '\0';
	  flag = 0;
	}
    }
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
  this->ip = inet_ntoa(client_sin.sin_addr);
  std::cout << "[clientAccept] New client added" << std::endl;
  return (cs);
}

std::string		LSocket::getIp(void) const
{
  return (this->ip);
}

void			LSocket::closeSocket(void)
{
  close(this->ListenSocket);
}

struct sockaddr_in*	LSocket::getSin(void)
{
  return (&this->sin);
}
