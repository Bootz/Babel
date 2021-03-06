/***********************************************************************
 * Module:  clientManager.h
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Declaration of the class clientManager
 ***********************************************************************/

#ifndef			__BABEL_CLIENTMANAGER_HPP__
# define		__BABEL_CLIENTMANAGER_HPP__

# include		<iostream>
# include		<vector>
# include		<string>
# include		"ServerClient.hpp"
# include		"BabelProtocol.hpp"
# include		"ISocket.hpp"

class			ClientManager
{
public:
  ClientManager(ISocket & sock);
  ~ClientManager();

  bool				add(const std::string & name,
				    const std::string & password,
				    const std::string & ip,
				    int socket);
  bool				deco(int id);
  ServerClient			getClient(const SOCKET sock) const;
  std::vector<ServerClient>	getClients() const;
  std::list<int>		getContacts(int fd) const;
  void				addContact(int fd, int contact);
  bool				isInList(unsigned short i)const;
  bool				isInList(std::string & name)const;
  void				delClient(int fd);
  int				getSocket(int id)const ;
  SOCKET			getSock(const std::string & name) const;
  std::string			getName(int id)const ;
  void				createClient(SOCKET sock);

private:
  std::vector<ServerClient>	_clients;
  std::string			_buffer;
  ISocket		&	_sock;
};

#endif			//__BABEL_CLIENTMANAGER_HPP__
