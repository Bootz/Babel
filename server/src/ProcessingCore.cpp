
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
    Protocol *protocol = static_cast<Protocol *>(cmd);
    bool ret = false;
    
    if (static_cast<size_t> (protocol->cmd) <= this->_command.size())
      ret = (this->*this->_command[protocol->cmd])(fdSock, *protocol);
    else
      this->sendError(fdSock, 400);
    return ret;
 }

//Enrgistre un client
bool			 ProcessingCore::cmdRegister(SOCKET fdSock, __attribute__ ((unused))Protocol protocol)
{
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
  return false;
}

// Authentifie un client
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
  
  //  Protocol protocol;
  InfoParam toSend;
  
  std::list<int> contacts;
  // creation de la list d'int correspondant aux login de la cmd
  if (infoParam->clientCount)
    {
      size_t loginsOffset = sizeof(*infoParam) - sizeof(infoParam->logins);
      
      for (int unsigned i = 0; i < infoParam->clientCount; ++i)
	{
	  char *tmp = static_cast<char*>(protocol.data) + loginsOffset + LEN_NAME * i;
	  std::string name = tmp;
	  //contacts.push_back(this->_clientsManager.getSock(name));
	}
    }
  
  // creer la InfoParam a renvoyer
  

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


bool			 ProcessingCore::cmdQuit(SOCKET fdSock, Protocol protocol)
{  
  // le serveur doit rompre la connexion avec ce client et le signaler aux autres. une fin de fichier est renvoyé sur la socket

  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  ServerClient *tmp = new ServerClient(this->_clientsManager.getClient(fdSock));
  
  // deconnecter propremment les sockets de tmp OU mettre tmp->setConneted(false);
  // Envoyer a tous ses contacts la commande CI_DECO
  return true;  
}

bool			 ProcessingCore::cmdEnd(SOCKET fdSock, __attribute__((unused))Protocol protocol)

{
  // envoie un msg a tous les clients, fermant la connexion
  // deconnecter toutes les sockets proprement
  return true;    
}

bool			 ProcessingCore::cmdCall(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  std::string login = registerParam->login;
  // Le serveur va transmettre un CC_INCOMING a login
  return true;  
}

bool			 ProcessingCore::cmdAccept(SOCKET fdSock, Protocol protocol)
{
  return this->sendRequest(fdSock, CI_ACCEPTED);
}

bool			 ProcessingCore::cmdRefuse(SOCKET fdSock, Protocol protocol)
{
 return  this->sendRequest(fdSock, CI_REFUSED);
}

bool			 ProcessingCore::cmdWait(SOCKET fdSock, Protocol protocol)
{
  return  this->sendRequest(fdSock, CI_PENDING);
}

bool			 ProcessingCore::cmdCcEnd(SOCKET fdSock, Protocol protocol)
{
  return  this->sendRequest(fdSock, CI_ENDED);
}

bool			 ProcessingCore::cmdSvEnd(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  // Le serveur envoie SV_END a tout les clients.
  // Le serveur clos proprement son reseau
  return true;
}

bool			ProcessingCore::sendError(SOCKET fdSock, int error)
{
  Protocol protocol;
  ErrorParam param;
      
  param.error = error;
  protocol.cmd = CI_ERROR;
  protocol.size = sizeof(param);
  std::memcpy(protocol.data, &param, protocol.size);
  this->_sock.send_d(fdSock, reinterpret_cast<char *> (&protocol));
}

bool			ProcessingCore::sendRequest(SOCKET fdSock, ProtocolCommand cmd)
{
  Protocol protocol;
  
  protocol.cmd = cmd;
  protocol.size = 0;
  protocol.data = NULL;
  this->_sock.send_d(fdSock, reinterpret_cast<char *> (&protocol));
}
