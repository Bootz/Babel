//
// WSocket.hh for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:43:50 2011 louis lesueur
// Last update Sun Nov 13 13:13:13 2011 louis lesueur
//

#ifndef			__BABEL_WSOCKET_HH__
# define		__BABEL_WSOCKET_HH__

# include		<winsock2.h>

class			WSocket : public ISocket
{
public:
  WSocket();
  virtual ~WSocket();

  virtual bool		connectToServer(std::string const & host, unsigned short port);
  virtual void		setAcceptSocket(SOCKET _sock);
  virtual SOCKET	getListenSocket(void)const;
  virtual SOCKET	getAcceptSocket(void)const;
  virtual int		send_d(SOCKET sock, const char* data);
  virtual int		recv_d(char* buffer);
  virtual int		getSocket() const;

private:
  WSocket(const WSocket & other);
  WSocket&		operator=(WSocket const & other);

private:
  static const int	SizeInterBuff = 9192;

private:
  int			SenderAddrSize;
  SOCKET		ListenSocket;
  SOCKET		AcceptSocket;
  struct SOCKADDR_IN	SenderAddr;
  struct SOCKADDR_IN	sin;

}

#endif			/*__BABEL_WSOCKET_HH*/
