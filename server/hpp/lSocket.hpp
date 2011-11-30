//
// Socket.hh for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:28:15 2011 louis lesueur
// Last update Tue Nov 22 15:50:06 2011 louis lesueur
//

#ifndef			__BABEL_LSOCKET_HH__
# define		__BABEL_LSOCKET_HH__

# include		<netinet/in.h>
# include		<sys/socket.h>
# include		<sys/types.h>
# include		<arpa/inet.h>
# include		<unistd.h>
# include		<iostream>
# include		<unistd.h>
# include		<netdb.h>
# include		"iSocket.hpp"

class			LSocket : public ISocket
{
 public:
  LSocket();
  LSocket(const LSocket & other);

public:
  virtual ~LSocket();
  virtual bool		connectToServer(std::string const& host, unsigned short port);
  virtual void		setAcceptSocket(SOCKET _sock);
  virtual SOCKET	getListenSocket(void)const;
  virtual SOCKET	getAcceptSocket(void)const;
  virtual int		send_d(SOCKET sock, std::string & str);
  virtual int		recv_d(SOCKET sock, std::string & str);
  virtual int		getSocket(void) const;
  virtual unsigned short	clientAccept(int s);

public:
  void			closeSocket(void);
  struct sockaddr_in*	getSin(void);


private:
  static const int	SizeInterBuff = 8192;

private:
  int			SenderAddrSize;
  SOCKET		ListenSocket;
  SOCKET		AcceptSocket;
  struct sockaddr_in	SenderAddr;
  struct sockaddr_in	sin;
  char *		buffer;
};

#endif			//__BABEL_LSOCKET_HH__
