//
// BabelProtocol.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 21:38:06 2011 by ramnes
// Last update Thu Nov 24 08:16:01 2011 ramnes
//

#ifndef		__BABEL_BABELPROTOCOL_HPP__
# define	__BABEL_BABELPROTOCOL_HPP__

#include       	<string>

class		BabelProtocol
{
public:
  BabelProtocol();
  ~BabelProtocol();

private:
  int		_cmd;
  void*		_data;
  size_t	_size;
  std::string	_checksum;

public:
  void		setRequest(int cmd, void* data, size_t size);
};

#endif		// __BABEL_BABELPROTOCOL_HPP__
