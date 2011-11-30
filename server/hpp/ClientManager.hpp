/***********************************************************************
 * Module:  clientManager.h
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Declaration of the class clientManager
 ***********************************************************************/

#ifndef			__BABEL_CLIENTMANAGER_HH__
# define		__BABEL_CLIENTMANAGER_HH__

# include		<iostream>
# include		<vector>
# include		<string>
# include		"ServerClient.hpp"
# include		"ISocket.hpp"

class			clientManager
{
public:
  clientManager(ISocket & sock);
  ~clientManager();

  bool				add(std::string name, std::string password, std::string ip, int socket);
  bool				isInList(unsigned short i);
  ServerClient &		find(std::string & name);
  int				getSocket(int id);
  std::string			getName(int id);
  bool				deco(int id);

private:
  std::vector<ServerClient>	_clients;
  std::string			_buffer;
  ISocket		&	_sock;
};

#endif			//__BABEL_CLIENTMANAGER_HH__
