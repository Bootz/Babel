/***********************************************************************
 * Module:  server.hh
 * Author:  Sioul
 * Modified: mercredi 16 novembre 2011 20:39:23
 * Purpose: Declaration of the class Server
 ***********************************************************************/


#ifndef		__BABEL_SERVER_HPP_
# define	__BABEL_SERVER_HPP_

# ifdef _WIN32
#  include "Socket_Win32.hpp"
#  else //unix
#  include "Socket_Linux.hpp"
# endif

# include		<string>
# include		<sys/select.h>
# include		<sys/time.h>
# include		<sys/types.h>
# include		<unistd.h>

# include		"ServerClient.hpp"
# include		"ISocket.hpp"
# include		"ProcessingCore.hpp"
# include		"ClientManager.hpp"


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
  bool			connectClients(ServerClient& caller, const std::string & name);
  void			setFd();
  bool			main_loop(void);

private:
  ISocket		*_serverSocket;
  ClientManager		_clientmanager;
  unsigned short	_nbClient;
  ProcessingCore	_proced;
  bool			_running;
  fd_set		_fdwrite;
  fd_set		_master;
  fd_set		_fdread;
  char			*_buffer;
  std::string		_ip;
  struct timeval	_tv;
};

#endif			//__BABEL_SERVER_HPP_
