//
// IClient.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 20:28:19 2011 by ramnes
// Last update Tue Nov 22 20:47:37 2011 ramnes
//

#ifndef		ICLIENT_HPP__
# define	ICLIENT_HPP__

#include	<string>

class		IClient
{
public:
  virtual	~IClient() {};

public:
  virtual bool	run() const = 0;
  virtual bool 	connectTo(const std::string& hostname, const int port) const = 0;
};

#endif		// ICLIENT_HPP__
