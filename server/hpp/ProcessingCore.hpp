#ifndef			__BABEL_PROCESSINGCORE_HH__
# define		__BABEL_PROCESSINGCORE_HH__

#include		<iostream>
#include		<vector>
#include		<utility>
#include		"ISocket.hpp"
#include		"ClientManager.hpp"

class ProcessingCore;

typedef bool		(ProcessingCore::*fct)(SOCKET sock, char *cmd);

class			ProcessingCore
{
public:
  ProcessingCore(ISocket &, ClientManager &, unsigned short &);
  ~ProcessingCore();

public:
  void			initialize();
  bool			extractCommand(std::string & command);

public:
  bool			cmdRegister(SOCKET fdSock, char *cmd);

private:
  ISocket &		_sock;
  ClientManager &	_clientsManager;
  unsigned short &	_nbClient;
  SOCKET		_actSock;
  std::vector<std::pair<int, fct> > _command;
  std::string		_buffer;
};

#endif			//__BABEL_PROCESSINGCORE_HH__
