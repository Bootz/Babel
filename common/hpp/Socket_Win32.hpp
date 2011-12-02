//
// WSocket.hh for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:43:50 2011 louis lesueur
// Last update Fri Dec  2 11:50:31 2011 louis lesueur
//

#ifndef			__BABEL_SOCKET_WIN32_HPP__
# define		__BABEL_SOCKET_WIN32_HPP__

# include		<winsock2.h>

class			WSocket : public ISocket
{
public:
  WSocket();
  virtual ~WSocket();

  virtual bool		connectToServer(std::string const & host, unsigned short port);
  virtual bool		initServer(unsigned short port);
  virtual void		setAcceptSocket(SOCKET _sock);
  virtual SOCKET	getListenSocket(void)const;
  virtual SOCKET	getAcceptSocket(void)const;
  virtual int		send_d(SOCKET sock, const char* data);
  virtual int		recv_d(char* buffer);
  virtual int		getSocket(void) const;
  virtual int		clientAccept(int s);
  virtual std::string	getIp(void) const;


private:
  WSocket(const WSocket & other) {};
  WSocket&		operator=(WSocket const & other) {};

public:
  void			closeSocket(void);
  struct sockaddr_in*	getSin(void)const ;

private:
  static const int	SizeInterBuff = 8192;

private:
  int			_SenderAddrSize;
  SOCKET		_ListenSocket;
  SOCKET		_AcceptSocket;
  struct SOCKADDR_IN	_SenderAddr;
  struct SOCKADDR_IN	_sin;
  char *		_buffer;
  std::string		_ip;
}

#endif			/*__BABEL_SOCKET_WIN32_HPP__
