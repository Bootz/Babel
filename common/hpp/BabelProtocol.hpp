//
// BabelProtocol.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 21:38:06 2011 by ramnes
// Last update Fri Dec  2 18:14:16 2011 louis lesueur
//

#ifndef		__BABEL_BABELPROTOCOL_HPP__
# define	__BABEL_BABELPROTOCOL_HPP__

#include       	<string>

class		BabelProtocol
{
public:
  BabelProtocol();
  BabelProtocol(unsigned int cmd, char *data, int size);
  BabelProtocol(BabelProtocol & other);
  ~BabelProtocol();

  void		setRequest(int cmd, void* data, size_t size);
public:
  char		*getData() const;
  size_t	getSize() const;
  unsigned int	getCmd() const;

private:
  unsigned int	_cmd;
  size_t	_size;
  char*		_data;
};

#endif		// __BABEL_BABELPROTOCOL_HPP__
