/***********************************************************************
 * Module:  serverClient.h
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Declaration of the class serverClient
 ***********************************************************************/

#ifndef		__BABEL_SERVERCLIENT_HPP__
# define	__BABEL_SERVERCLIENT_HPP__

# include		<string>
# include		<list>
# include		"ISocket.hpp"

class			ServerClient
{
public:
  ServerClient(SOCKET & sock, std::string name);
  ServerClient(const std::string & name,
	       const std::string & password,
	       const std::string &ip,
	       int socket);
  ~ServerClient();

  ServerClient& operator=(const ServerClient&);

public:
  void			setSocket(int sock);

  std::list<int>	getContacts() const;
  std::string		getPassword() const;
  bool			isConnected() const;
  int			getSocket() const;
  std::string		getName() const;
  std::string		getIp() const;

private:

  std::string		_password;
  bool			_connected;
  std::list<int>	_contacts;
  std::string		_name;
  std::string		_ip;
  int			_socket;
};

#endif			//__BABEL_SERVERCLIENT_HPP__
