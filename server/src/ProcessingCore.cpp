
#include		<iostream>
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

bool			ProcessingCore::commandChoice(SOCKET sock, void *cmd)
  {
    std::cout << "[ProcessingC] Choix de la commande" << std::endl;
    Protocol *protocol = static_cast<Protocol *>(cmd);
    std::cout << "[ProcessingC] cmd = " << cmd << "."  << std::endl;
    bool ret = false;
    
    if (static_cast<size_t> (protocol->cmd) <= this->_command.size())
      {
	ret = (this->*this->_command[protocol->cmd])(sock, *protocol);
      }
    else
      std::cout << "[ProcessingC] Commande inconnue" << std::endl;
    return ret;
 }


// faire un fct() pour choper le client via le fdSock!
// this->_clientsManager.getClient(fdSock)


bool			 ProcessingCore::cmdRegister(SOCKET fdSock, __attribute__ ((unused))Protocol protocol)
{
  
  // faire un add du client avec ses parametres
  // /!\ client->_connected == false

  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);

  std::string name = registerParam->login;
  std::string password = registerParam->password;
  std::cout << "[cmdRegister]login = " << name << " password = " << password << std::endl;
  this->_clientsManager.add(name, password, this->_sock.getIp(), fdSock);
  ++this->_nbClient;
  return true;
}


bool			 ProcessingCore::cmdLogin(SOCKET fdSock, Protocol protocol)
{
// Authentifie un client
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  std::string name = this->_clientsManager.getClient(fdSock).getName();
  if (this->_clientsManager.isInList(name))
    this->_clientsManager.getClient(fdSock).setConnected(true);
  // si non, renvoyer 403 ERR_FORBIDDEN -- accès refusé (login ou mot de passe invalide)

  return true;
}

bool			 ProcessingCore::cmdInfo(SOCKET fdSock, Protocol protocol)
{
  // Le serveur envoie les informations de chaque client passé en paramètre. Si aucun paramètre, le serveur envoie les infos de tous les clients connectés.

  const InfoParam* infoParam = static_cast<const InfoParam*>(protocol.data);
  
  InfoParam toSend;
  
  for (std::vector<ServerClient>::iterator it = this->_clientsManager.getClients().begin();
       it < this->_clientsManager.getClients().end();
       ++it)
    if (infoParam->clientCount == 0)
      {
	if (it->isConnected())
	  {
	    //ajouter le client a la structure toSend, evaec le bon nombre de clients, etc
	  }
      }
    else
      ;//ajouter le client a la structure toSend, evaec le bon nombre de clients, etc
      
  // envoyer toSend par le reseau;
  
  return true;
  // size_t loginsOffset = sizeof(*infoParam) - sizeof(infoParam->logins);
  // for (int unsigned i = 0; i < infoParam->clientCount; ++i)
  //   {
  //     char* currentLogin = static_cast<char*>(protocol.data) + loginsOffset + LEN_NAME * i;
  //     std::cout << currentLogin << std::endl;
  //   }
}


bool			 ProcessingCore::cmdQuit(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  // le serveur doit rompre la connexion avec ce client et le signaler aux autres. une fin de fichier est renvoyé sur la socket

  // choper le client dans la liste via fdSock
  // deconnecter ses sockets proprement
  // Envoyer a tous ses contacts une commande qui n'existe pas encore

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
  
  return true;  
}

bool			 ProcessingCore::cmdAccept(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  
  return true;
}

bool			 ProcessingCore::cmdRefuse(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  return true;
}

bool			 ProcessingCore::cmdWait(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);

  return true;
}

bool			 ProcessingCore::cmdCcEnd(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  return true;
}

bool			 ProcessingCore::cmdSvEnd(SOCKET fdSock, Protocol protocol)
{
  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);
  
  return true;
}
