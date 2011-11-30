/***********************************************************************
 * Module:  server.hh
 * Author:  Sioul
 * Modified: mercredi 16 novembre 2011 20:39:23
 * Purpose: Declaration of the class Server
 ***********************************************************************/


#ifndef		__BABEL_SERVER_HH_
# define	__BABEL_SERVER_HH_

# ifdef WIN32
#  include "wSocket.hh"
#  else //unix
#  include "lSocket.hh"
# endif

# include		<string>
# include		<sys/select.h>
# include		<sys/time.h>
# include		<sys/types.h>
# include		<unistd.h>

# include		"serverClient.hh"
# include		"iSocket.hh"
# include		"processingCore.hh"
# include		"clientManager.hh"


class			Server
{
public:
  static Server&	getInstance();

private:
  Server();
  ~Server();

private:
  static Server		onlyInstance;

public:
  bool			connectClients(ServerClient& caller, std::string name);
  void			setFd(const int fd);
  bool			main_loop(void);

private:
  ISocket		*serverSocket;
  clientManager		clientmanager;
  unsigned short	nbClient;
  ProcessingCore	proced;
  bool			running;
  fd_set		fdwrite;
  fd_set		fdread;
  std::string		buffer;
  std::string		ip;
};

#endif			//__BABEL_SERVER_HH_
