//
// WSocket.cpp for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:43:15 2011 louis lesueur
// Last update Fri Nov 18 15:38:52 2011 louis lesueur
//

#include		"Exception.hpp"
#include		"WSocket.hpp"

WSocket::WSocket()
  : ListenSocket(-1),
    AcceptSocket(-1)
{
  this->SenderAddrSize = sizeof(this->SenderAddr);
}

WSocket::~WSocket()
{
  close(this->ListenSocket);
}

void			WSocket::closeSocket(void)
{
  close(this->ListenSocket);
}

int			WSocket::getSocket() const
{
  return (ListenSocket);
}

bool			WSocket::connectToServer(std::string const& host, unsigned short port)
{
  if ((this->ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    throw babel_exception("[WINDOWS] Error at WSASocket()");
  this->sin.sin_family = AF_INET;
  this->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  this->sin.sin_port = htons(port);
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
	throw babel_exception("[ERROR] recv() operation failed");
      if (nbr >= size || (nbr >= 1 && buf[nbr-1] == '\n') ||
	  (nbr >= 2 && buf[nbr-2] == '\n' && buf[nbr-1] == '\r'))
	{
	  buf[nbr] = '\0';
	  break;
	}
    }
  return (nb_read);
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
	throw babel_exception("[ERROR] send() operation failed");
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

struct SOCKADDR_IN*	WSocket::getSin(void)
{
  return (&this->sin);
}

void			WSocket::setAcceptSocket(SOCKET _sock)
{
  this->AcceptSocket = _sock;
}
