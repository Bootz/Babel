#ifndef			__BABEL_PROCESSINGCORE_HH__
# define		__BABEL_PROCESSINGCORE_HH__

#include		<iostream>
#include		<vector>
#include		<utility>
#include		"ISocket.hpp"
#include		"ClientManager.hpp"

class			ProcessingCore
{
public:
  ProcessingCore(ISocket &, ClientManager &, unsigned short &);
  ~ProcessingCore();

private:
typedef bool		(ProcessingCore::*fct)(SOCKET sock, char *cmd);

public:
  void			initialize();
  bool			extractCommand(SOCKET sock, void *);

public:
  bool			cmdRegister(SOCKET fdSock, char *cmd);
  bool			cmdLogin(SOCKET fdSock, char *cmd);
  bool			cmdInfo(SOCKET fdSock, char *cmd);
  bool			cmdQuit(SOCKET fdSock, char *cmd);
  bool			cmdEnd(SOCKET fdSock, char *cmd);

private:
  ISocket &		_sock;
  ClientManager &	_clientsManager;
  unsigned short &	_nbClient;
  SOCKET		_actSock;
  std::vector<fct>	 _command; // c'est quoi cet int?
  std::string		_buffer;
};

#endif			//__BABEL_PROCESSINGCORE_HH__
