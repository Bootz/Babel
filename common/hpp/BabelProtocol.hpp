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

typedef struct BabelProtocol
{
private:
  int		_cmd;
  size_t	_size;
  char*		_data;
  std::string	_checksum;

public:
  int		getCmd(void) const;
  size_t	getSize(void) const;
  char*		getData(void) const;
  std::string	getChecksum(void) const;

  void		setCmd(int cmd);
  void		setSize(size_t size);
  void		setData(char *data);
  void		setChecksum(char *checksum);

public:
  void		setRequest(int cmd, void* data, size_t size);

} t_babelProtcol;

#endif		// __BABEL_BABELPROTOCOL_HPP__
