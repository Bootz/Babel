//
// WSocket.cpp for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:43:15 2011 louis lesueur
// Last update Sun Dec  4 15:13:48 2011 louis lesueur
//

#include		"Exception.hpp"
#include		"Socket_Win32.hpp"

WSocket::WSocket()
  : ListenSocket(-1),
    AcceptSocket(-1)
{
  this->SenderAddrSize = sizeof(this->SenderAddr);
  this->buffer = new char[this->SizeInterBuff];}

WSocket::~WSocket()
{
  close(this->ListenSocket);
}

void			WSocket::closeSocket(void)
{
  close(this->ListenSocket);
}

std::string		WSocket::getIp(void) const
{
  return (this->_ip);
}

int			WSocket::getSocket() const
{
  return (ListenSocket);
}

bool			WSocket::connectToServer(std::string const& host, unsigned short port)
{
  struct protoent*	pe;

  this->_ip = host;
  pe = getprotobyname("tcp");
  if ((this->ListenSocket = WSASocket(AF_INET, SOCK_STREAM, pe->p_proto, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    throw BabelException("[WINDOWS] Error at WSASocket()");
  if (this->ListenSocket == -1)
    throw babel_exception("[WINDOWS] Error at socket()");
  this->sin.sin_family = AF_INET;
  if (host != "INADDR_ANY")
    this->sin.sin_addr.s_addr = inet_addr(host.c_str());
  else
    this->sin.sin_addr.s_addr = INADDR_ANY;
  this->sin.sin_port = htons(port);
  return (true);
}

bool			WSocket::initServer(unsigned short port)
{
  struct sockaddr_in   addr;

  if ((this->ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    throw BabelException("[WINDOWS] Error at WSASocket()");
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

int			WSocket::recv_d(char* buf)
{
  int			nb_read = 0;
  int			nbr = 0;
  int			size = SizeInterBuff;

  while (42)
    {
      nb_read = WSARecv(this->ListenSocket, (buf + nbr), SizeInterBuff - nbr, 0, 0, 0);
      nbr += nb_read;
      if (nb_read < 0)
	throw BabelException("[ERROR] recv() operation failed");
      if (nbr >= size || (nbr >= 1 && buf[nbr-1] == '\n') ||
	  (nbr >= 2 && buf[nbr-2] == '\n' && buf[nbr-1] == '\r'))
	{
	  buf[nbr] = '\0';
	  break;
	}
    }
  return (nb_read);
}

int			WSocket::clientAccept(int s)
{
  unsigned int		client_sin_len;
  struct sockaddr_in    client_sin;
  int			cs;

  client_sin_len = sizeof(client_sin);
  if ((cs = WSAAccept(s, (struct sockaddr *)&client_sin, &client_sin_len, NULL, NULL)) < 0)
    throw BabelException("[ERROR] accept() operation failed");
  this->_ip = inet_ntoa(client_sin.sin_addr);
  std::cout << "[clientAccept] New client added" << std::endl;
  return (cs);
}

int			WSocket::send_d(SOCKET sock, const char* data)
{
  int			nb_write;
  int			tmp;
  int			size;

  size = strlen(data);
  tmp = 0;
  nb_write = 0;
  while (tmp != size)
    {
      nb_write = WSASend(this->ListenSocket, (data + tmp), strlen((data + tmp)), 0, 0, 0);
      if (nb_write == -1)
	throw BabelException("[ERROR] send() operation failed");
      tmp += nb_write;
    }
  return (nb_write);
}

SOCKET			WSocket::getListenSocket(void)const
{
  return (this->ListenSocket);
}

SOCKET			WSocket::getAcceptSocket(void)const
{
  return (this->AcceptSocket);
}

struct SOCKADDR_IN*	WSocket::getSin(void) const
{
  return (&this->sin);
}

void			WSocket::setAcceptSocket(SOCKET _sock)
{
  this->AcceptSocket = _sock;
}
