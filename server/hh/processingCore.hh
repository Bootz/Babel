#ifndef			__BABEL_PROCESSINGCORE_HH__
# define		__BABEL_PROCESSINGCORE_HH__

#include		<iostream>
#include		<vector>
#include		<utility>
#include		"iSocket.hh"
#include		"clientManager.hh"

class ProcessingCore;

typedef bool		(ProcessingCore::*fct)(SOCKET sock, std::string cmd);

class			ProcessingCore
{
public:
  //  ProcessingCore();
  ProcessingCore(short unsigned int nb_client);
  ~ProcessingCore();

public:
  void			initialize();
  bool			extractCommand(std::string & command);

public:
  bool			cmdRegister(SOCKET fdSock, std::string cmd);

public:
  void			setSocket(ISocket *);
  void			setClientmanager(clientManager *);
  void			setNbClient(unsigned short int);

private:
  SOCKET		_actSock;
  std::vector<std::pair<std::string, fct> > _command;
  clientManager *	_clientsManager;
  unsigned short &	_nbClient;
  ISocket *		_sock;
  std::string		_buffer;
};

#endif			//__BABEL_PROCESSINGCORE_HH__
