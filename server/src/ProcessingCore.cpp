
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
  fct   End(&ProcessingCore::cmdEnd);
  this->_command.push_back(Register);
  this->_command.push_back(Login);
  this->_command.push_back(Info);
  this->_command.push_back(Quit);
  this->_command.push_back(End);
}

bool			ProcessingCore::commandChoice(SOCKET sock, void *cmd)
  {
    Protocol *protocol = static_cast<Protocol *>(cmd);
    bool ret;

    if (static_cast<size_t> (protocol->cmd) <= this->_command.size())
      {
	ret = (this->*this->_command[protocol->cmd])(sock, *protocol);
      }
    delete protocol;
    return ret;
 }

bool			 ProcessingCore::cmdRegister(SOCKET fdSock, __attribute__ ((unused))Protocol protocol)
{
// enregistrer le login et le paswd
// Louis, je te laisse gerer ça

  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);

  std::string name = registerParam->login;
  std::string password = registerParam->password;

  std::cout << "login = " << name << " password = " << password << std::endl;
  // std::string		password;
  // unsigned short	sock;
  // std::string		name;
  // std::string		buf;
  // int			pos;
  // int			i;

  // i = 0;
  // sock = this->_sock.clientAccept(fdSock);
  // this->_sock.recv_d(sock, this->_buffer);
  // for (; buf[i] == ' '; ++i);
  // pos = i;
  // buf.find(' ', i);
  // name.assign(buf, pos, i - pos);
  // for (; buf[i] == ' '; ++i);
  // pos = i;
  // if (buf.find(' ', i) == std::string::npos)
  //   password.assign(buf, pos, buf.size() - pos);
  // else
  //   password.assign(buf, pos, i - pos);
  // this->_clientsManager.add(name, password, this->_sock.getIp(), sock);
  // ++this->_nbClient;

  delete registerParam;
  return true;
}


bool			 ProcessingCore::cmdLogin(SOCKET fdSock, Protocol protocol)
{
// Authentifie un client

  const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol.data);

// Choper son name, verifier si il existe dans la liste de client
// si oui, changer son _connected
// si non, renvoyer 403 ERR_FORBIDDEN -- accès refusé (login ou mot de passe invalide)

  delete registerParam;
  return true;
}

bool			 ProcessingCore::cmdInfo(SOCKET fdSock, Protocol protocol)
{
// Le serveur envoies les informations de chaque client passé en paramètre. Si aucun paramètre, le serveur envoie les infos de tous les clients connectés.

  const InfoParam* infoParam = static_cast<const InfoParam*>(protocol.data);
  
  //choper la liste de clients (dans une std::list par exemple)
  //renvoyer les infos de chacun des clients (quelles infos)
// si un login n'existe pas, ne pas le prendre en compte ?

  size_t loginsOffset = sizeof(*infoParam) - sizeof(infoParam->logins);
    for (int unsigned i = 0; i < infoParam->clientCount; ++i)
      {
	char* currentLogin = static_cast<char*>(protocol.data) + loginsOffset + LEN_NAME * i;
	std::cout << currentLogin << std::endl;
      }
    delete infoParam;
    
  return true;
}


bool			 ProcessingCore::cmdQuit(SOCKET fdSock, Protocol protocol)
{
// le serveur doit rompre la connexion avec ce client et le signaler aux autres. une fin de fichier est renvoyé sur la socket

// choper le client dans la liste
// deconnecter ses sockets proprement
// Envoyer a tous ses contacts 
  return true;  
}

// envoie un msg a tous les clients, fermant la connexion
bool			 ProcessingCore::cmdEnd(SOCKET fdSock, Protocol protocol)
{
  return true;    
}
