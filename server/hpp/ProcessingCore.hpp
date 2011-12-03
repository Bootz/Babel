
#ifndef			__BABEL_PROCESSINGCORE_HH__
# define		__BABEL_PROCESSINGCORE_HH__

#include		<iostream>
#include		<vector>
#include		<utility>
#include		"ISocket.hpp"
#include		"ClientManager.hpp"
#include		"BabelProtocol.hpp"

class			ProcessingCore
{
public:
  ProcessingCore(ISocket &, ClientManager &, unsigned short &);
  ~ProcessingCore();

private:
typedef bool		(ProcessingCore::*fct)(SOCKET sock, Protocol proto);

public:
  void			initialize();
  bool			extractCommand(SOCKET sock, void *);

public:
  bool			cmdRegister(SOCKET fdSock, Protocol proto);
  bool			cmdLogin(SOCKET fdSock, Protocol proto);
  bool			cmdInfo(SOCKET fdSock, Protocol proto);
  bool			cmdQuit(SOCKET fdSock, Protocol proto);
  bool			cmdEnd(SOCKET fdSock, Protocol proto);

private:
  ISocket &		_sock;
  ClientManager &	_clientsManager;
  unsigned short &	_nbClient;
  SOCKET		_actSock;
  std::vector<fct>	 _command; // c'est quoi cet int?
  std::string		_buffer;
};

#endif			//__BABEL_PROCESSINGCORE_HH__
