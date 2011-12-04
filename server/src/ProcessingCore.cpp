       
#include		<iostream>
#include		<cstdio>
#include		<cstring>
#include		"ProcessingCore.hpp"
#include		"BabelProtocol.hpp"

ProcessingCore::ProcessingCore(ISocket & sock, ClientManager & cm, unsigned short& nbclient)
  : _sock(sock),
    _clientsManager(cm),
    _nbClient(nbclient)
{
}

ProcessingCore::~ProcessingCore()
{
}

void ProcessingCore::initialize()
{
  fct   Register(&ProcessingCore::cmdRegister);
  fct   Login(&ProcessingCore::cmdLogin);
  fct   Info(&ProcessingCore::cmdInfo);
  fct   Quit(&ProcessingCore::cmdQuit);
  fct   Call(&ProcessingCore::cmdCall);
  fct   Accept(&ProcessingCore::cmdAccept);
  fct   Refuse(&ProcessingCore::cmdRefuse);
  fct   Wait(&ProcessingCore::cmdWait);
  fct   CcEnd(&ProcessingCore::cmdCcEnd);
  fct   SvEnd(&ProcessingCore::cmdSvEnd);
  this->_command.push_back(Register);
  this->_command.push_back(Login);
  this->_command.push_back(Info);
  this->_command.push_back(Quit);
  this->_command.push_back(Call);
  this->_command.push_back(Accept);
  this->_command.push_back(Refuse);
  this->_command.push_back(Wait);
  this->_command.push_back(CcEnd);
  this->_command.push_back(SvEnd);
}

bool			ProcessingCore::commandChoice(SOCKET fdSock, void *cmd)
  {
    std::cout << "[CMDchoice]" << std::endl;
    Protocol *protocol = static_cast<Protocol *>(cmd);
    bool ret = false;
        std::cout << "[CMDchoice2]" << std::endl;
    if (static_cast<size_t> (protocol->cmd) <= this->_command.size())
      {
	std::cout << "[CMDchoice] commande connue : [" << cmd << "]." << std::endl;
	ret = (this->*this->_command[protocol->cmd])(fdSock, *protocol);
      }
    else
      {
	std::cout << "[CMDchoice] commande non connue" << std::endl;
	this->sendError(fdSock, 400);
	std::cout << "[CMDchoice] commande non connue2" << std::endl;
      }
    return ret;
 }

//Enregistre un client : Done
bool			 ProcessingCore::cmdRegister(SOCKET fdSock, Protocol protocol)
{
  std::cout << "[cmdRegister]";
  if (! this->_clientsManager.getClient(fdSock).isConnected())
    {
      const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);

      std::string login = registerParam->login;
      std::string password = registerParam->password;
      std::cout << "[cmdRegister]login = " << login << " password = " << password << std::endl;
      this->_clientsManager.add(login, password, this->_sock.getIp(), fdSock);
      ++this->_nbClient;
      return true;
    }
  this->sendError(fdSock, 400);
  std::cout << "[cmdRegister] end";
  return false;
}

// Authentifie un client : Done
bool			 ProcessingCore::cmdLogin(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  std::string login = registerParam->login;

  if (this->_clientsManager.isInList(login))
    {
      this->_clientsManager.getClient(fdSock).setConnected(true);
      for (std::list<int>::iterator it = this->_clientsManager.getContacts(fdSock).begin();
	   it != this->_clientsManager.getContacts(fdSock).end();
	   ++it)
	if (this->_clientsManager.getClient(*it).isConnected())
	  this->sendRequest(*it, CI_DECO);
    }
  else
    this->sendError(fdSock, 403);
  return true;
}

// Le serveur envoie les informations de chaque client passé en paramètre. Si aucun paramètre, le serveur envoie les infos de tous les clients connectés.
bool			 ProcessingCore::cmdInfo(SOCKET fdSock, Protocol protocol)
{
  const InfoParam* infoParam = static_cast<const InfoParam*>(protocol.data);

  Protocol toSendproto;
  InfoParam toSendparam;

  std::list<int> contacts;
  // creation de la list d'int correspondant aux login de la cmd
  if (infoParam->clientCount)
    {
      toSendparam.clientCount = infoParam->clientCount;
      size_t loginsOffset = sizeof(*infoParam) - sizeof(infoParam->logins);

      for (int unsigned i = 0; i < infoParam->clientCount; ++i)
	{
	  char *tmp = static_cast<char*>(protocol.data) + loginsOffset + LEN_NAME * i;
	  std::string name = tmp;
	  //contacts.push_back(this->_clientsManager.getSock(name));
	}
    }
  
  toSendproto.cmd = CL_INFO;
  toSendproto.size = sizeof(toSendparam);
  // creer la InfoParam a renvoyer
  //std::memcpy(toSendproto.data, &toSendparam, protocol.size);
  this->_sock.send_d(fdSock, reinterpret_cast<char *> (&protocol));

  // for (std::vector<ServerClient>::iterator it = this->_clientsManager.getClients().begin();
  //      it < this->_clientsManager.getClients().end();
  //      ++it)
  //   if (infoParam->clientCount == 0)
  //     {
  // 	if (it->isConnected())
  // 	  {
  // 	    ++infoParam->clientCount;

  // 	    ;//ajouter le client a la structure toSend, avec le bon nombre de clients, etc
  // 	  }
  //     }
  //   else
  //     {
  // 	;//ajouter le client a la structure toSend, evaec le bon nombre de clients, etc
  //     }
  return true;

  // exemple d'utilisation de la struct Protocol
  //
}


// Done
bool			 ProcessingCore::cmdQuit(SOCKET fdSock, __attribute__((unused))Protocol protocol)
{

  ServerClient *tmp = new ServerClient(this->_clientsManager.getClient(fdSock));

  tmp->setConnected(false);
  for (std::list<int>::iterator it = this->_clientsManager.getContacts(fdSock).begin();
       it != this->_clientsManager.getContacts(fdSock).end();
       ++it)
    if (this->_clientsManager.getClient(*it).isConnected())
      this->sendRequest(*it, CI_DECO);
  return true;
}

bool			 ProcessingCore::cmdCall(SOCKET fdSock, __attribute__((unused)) Protocol protocol)
{
  return this->sendRequest(fdSock, CI_ACCEPTED);
}

bool			 ProcessingCore::cmdAccept(SOCKET fdSock, __attribute__((unused)) Protocol protocol)
{
  return this->sendRequest(fdSock, CI_ACCEPTED);
}

bool			 ProcessingCore::cmdRefuse(SOCKET fdSock, __attribute__((unused)) Protocol protocol)
{
 return  this->sendRequest(fdSock, CI_REFUSED);
}

bool			 ProcessingCore::cmdWait(SOCKET fdSock, __attribute__((unused)) Protocol protocol)
{
  return  this->sendRequest(fdSock, CI_PENDING);
}

bool			 ProcessingCore::cmdCcEnd(SOCKET fdSock, __attribute__((unused)) Protocol protocol)
{
  return  this->sendRequest(fdSock, CI_ENDED);
}

bool			 ProcessingCore::cmdSvEnd(SOCKET fdSock, __attribute__((unused))Protocol protocol)
{
  // envoie de SV_END a tout les clients
  for (std::list<int>::iterator it = this->_clientsManager.getContacts(fdSock).begin();
       it != this->_clientsManager.getContacts(fdSock).end();
       ++it)
    {
      this->sendRequest(*it, SV_END);
      this->_clientsManager.getClient(*it).setConnected(false);
    }
    
  // Close() de toutes les sockets ouvertes
  for (int i = this->_sock.getListenSocket();
       i != static_cast <int> (this->_clientsManager.getClients().size());
       ++i)
    close(i);
  return true;
}

bool			ProcessingCore::sendError(SOCKET fdSock, int error)
{
  Protocol *protocol = new Protocol;
  ErrorParam *param = new ErrorParam;

  std::cout << "[sendError]end" << std::endl;
  param->error = error;
  std::cout << "[sendError]end" << std::endl;
  protocol->cmd = CI_ERROR;
  std::cout << "[sendError]end" << std::endl;
  protocol->size = sizeof(*param);
  std::cout << "[sendError]end" << std::endl;
  std::memcpy(&protocol->data, param, protocol->size);
  std::cout << "[sendError]end" << std::endl;
  try
    {
      std::cout << "[sendError]try" << std::endl;
      this->_sock.send_d(fdSock, reinterpret_cast<char *> (&protocol));
    }
  catch (const std::exception &)
    {
      std::cout << "[sendError]catch" << std::endl;
      std::cerr << "[ERROR] Client [" << fdSock << "] has been disconnected" << std::endl;
      this->cmdQuit(fdSock, *protocol);
      return false;
    }
  std::cout << "[sendError]end" << std::endl;
  delete protocol;
  delete param;
  return true;
}

bool			ProcessingCore::sendRequest(SOCKET fdSock, ProtocolCommand cmd)
{
  Protocol protocol;

  protocol.cmd = cmd;
  protocol.size = 0;
  protocol.data = NULL;
  try
    {
      this->_sock.send_d(fdSock, reinterpret_cast<char *> (&protocol));
    }
  catch (const std::exception &)
    {
      std::cerr << "[ERROR] Client [" << fdSock << "] has been disconnected" << std::endl;
      (this->*this->_command[CL_QUIT])(fdSock, protocol);
      return false;
    }
  return true;
}
