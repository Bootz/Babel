//
// BabelClient.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 18:18:37 2011 by ramnes
// Last update Sun Dec  4 16:39:57 2011 guillaume gelin
//

#ifndef		BABELCLIENT_HPP__
# define	BABELCLIENT_HPP__

# include	<map>
#include	<sys/time.h>
#include	<sys/select.h>
#include	<sys/types.h>

# include	"IClient.hpp"
# include	"BabelProtocol.hpp"
# include	"ISocket.hpp"
# include	"Socket_Linux.hpp"

# define	DEFAULT_MASTER "master.babel.net"
# define	DEFAULT_PORT 8483

class		BabelClient : public IClient
{
public:
  BabelClient();
  ~BabelClient();

private:
  std::map<std::string, std::string> _config;
  LSocket	_socket;
  fd_set	_fdread;
  fd_set	_fdwrite;
  timeval	_timeval;

public:
  virtual bool	run();
  virtual bool	connectTo(const std::string& hostname, const int port);
  bool		connectTo();

public:
  bool		sendData(const Protocol& data);
  bool		loadConfig(const std::string& filename);
};

#endif		// BABELCLIENT_HPP__
