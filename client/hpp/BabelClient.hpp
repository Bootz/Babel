//
// BabelClient.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 18:18:37 2011 by ramnes
// Last update Thu Nov 24 11:52:11 2011 ramnes
//

#ifndef		BABELCLIENT_HPP__
# define	BABELCLIENT_HPP__

# include	<map>

# include	"IClient.hpp"
# include	"BabelProtocol.hpp"

# define	DEF_MASTER "master.babel.net"
# define	DEF_PORT 8483

class		BabelClient : public IClient
{
public:
  BabelClient();
  ~BabelClient();

private:
  std::map<std::string, std::string> _cfg;

public:
  virtual bool	run();
  virtual bool	connectTo(const std::string& hostname, const int port) const;
  bool		connectTo();

public:
  bool		sendData(const BabelProtocol& data);
  bool		loadCfg(const std::string& filename);
};

#endif		// BABELCLIENT_HPP__
