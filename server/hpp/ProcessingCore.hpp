#ifndef			__BABEL_PROCESSINGCORE_HH__
# define		__BABEL_PROCESSINGCORE_HH__

#include		<iostream>
#include		<vector>
#include		<utility>
#include		"ISocket.hpp"
#include		"ClientManager.hpp"

class ProcessingCore;

typedef bool		(ProcessingCore::*fct)(SOCKET sock, std::string cmd);

class			ProcessingCore
{
public:
  ProcessingCore(ISocket &, clientManager &, unsigned short &);
  ~ProcessingCore();

public:
  void			initialize();
  bool			extractCommand(std::string & command);

public:
  bool			cmdRegister(SOCKET fdSock, std::string cmd);

private:
  ISocket &		_sock;
  clientManager &	_clientsManager;
  unsigned short &	_nbClient;
  SOCKET		_actSock;
  std::vector<std::pair<std::string, fct> > _command;
  std::string		_buffer;
};

#endif			//__BABEL_PROCESSINGCORE_HH__
