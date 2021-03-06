//
// ISocket.hh for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:28:27 2011 louis lesueur
// Last update Sun Dec  4 06:02:52 2011 louis lesueur
//

#ifndef			__BABEL_ISOCKET_HHP__
# define		__BABEL_ISOCKET_HHP__

typedef int		 SOCKET;

class ISocket
{
 public:
  virtual ~ISocket() {}

  virtual bool		connectToServer(std::string const&, unsigned short port) = 0;
  virtual bool		initServer(unsigned short port) = 0;
  virtual void		setAcceptSocket(SOCKET _sock) = 0;
  virtual SOCKET	getListenSocket(void)const = 0;
  virtual SOCKET	getAcceptSocket(void)const = 0;
  virtual int		send_d(SOCKET sock, char *tmp) = 0;
  virtual int		recv_d(SOCKET sock, char *tmp) = 0;
  virtual int		getSocket() const = 0;
  virtual int		clientAccept(int s) = 0;
  virtual void		closeSocket(void) = 0;
  virtual std::string	getIp(void) const = 0;
};

#endif			/*__BABEL_ISOCKET_HHP__*/
