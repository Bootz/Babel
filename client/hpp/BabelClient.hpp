//
// BabelClient.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 18:18:37 2011 by ramnes
// Last update Tue Nov 22 20:53:12 2011 ramnes
//

#ifndef		BABELCLIENT_HPP__
# define	BABELCLIENT_HPP__

# include	"IClient.hpp"
# define	MASTER	"192.168.0.1"
# define	PORT	1337

class		BabelClient : public IClient
{
private:

public:
  BabelClient();
  ~BabelClient();

public:
  virtual bool	run() const;
  virtual bool	connectTo(const std::string& hostname, const int port) const;
};

#endif		// BABELCLIENT_HPP__
