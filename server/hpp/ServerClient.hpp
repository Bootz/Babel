/***********************************************************************
 * Module:  serverClient.h
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Declaration of the class serverClient
 ***********************************************************************/

#ifndef		__BABEL_SERVERCLIENT_HH__
# define	__BABEL_SERVERCLIENT_HH__

# include		<string>
# include		<list>

class			ServerClient
{
public:
  ServerClient(std::string name, std::string password, std::string ip, unsigned short id, int socket);
  //  ServerClient& operator=(const ServerClient&);
  ~ServerClient();

public:
  std::string		getName() const;
  unsigned short	getId() const;
  std::string		getIp() const;
  int			getSocket() const;
  std::list<int>	getContacts() const;

private:

  std::string		_password;
  bool			_connected;
  std::list<int>	_contacts;
  std::string		_name;
  std::string		_ip;
  unsigned short	_id;
  int			_socket;
};

#endif			//__BABEL_SERVERCLIENT_HH__
