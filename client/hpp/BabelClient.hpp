//
// BabelClient.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 18:18:37 2011 by ramnes
// Last update Tue Nov 22 23:08:59 2011 ramnes
//

#ifndef		BABELCLIENT_HPP__
# define	BABELCLIENT_HPP__

# include	"IClient.hpp"
# include	"BabelProtocol.hpp"

class		BabelClient : public IClient
{
public:
  BabelClient();
  ~BabelClient();

private:

public:
  virtual bool	run() const;
  virtual bool	connectTo(const std::string& hostname, const int port) const;

public:
  bool		sendData(const BabelProtocol& data);
};

#endif		// BABELCLIENT_HPP__
