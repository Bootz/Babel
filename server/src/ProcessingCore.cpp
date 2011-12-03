
#include		"ProcessingCore.hpp"
#include		"BabelProtocol.hpp"
// ProcessingCore::ProcessingCore()
// {

// }

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

bool			ProcessingCore::extractCommand(SOCKET sock, void *cmd)
 {
   BabelProtocol *tmp = static_cast<BabelProtocol *>(cmd);
   
   if (static_cast<size_t> (tmp->getCmd()) <= this->_command.size())
     return (this->*this->_command[tmp->getCmd()])(sock, tmp->getData());// mon petit bijou
   return false;
 }

bool			 ProcessingCore::cmdRegister(SOCKET fdSock, __attribute__ ((unused))char *cmd)
{
  std::string		password;
  unsigned short	sock;
  std::string		name;
  std::string		buf;
  int			pos;
  int			i;

  i = 0;
  sock = this->_sock.clientAccept(fdSock);
  this->_sock.recv_d(sock, this->_buffer);
  for (; buf[i] == ' '; ++i);
  pos = i;
  buf.find(' ', i);
  name.assign(buf, pos, i - pos);
  for (; buf[i] == ' '; ++i);
  pos = i;
  if (buf.find(' ', i) == std::string::npos)
    password.assign(buf, pos, buf.size() - pos);
  else
    password.assign(buf, pos, i - pos);
  this->_clientsManager.add(name, password, this->_sock.getIp(), sock);
  ++this->_nbClient;
  return true;
}

bool			 ProcessingCore::cmdLogin(SOCKET fdSock, char *cmd)
{
  return true;  
}

bool			 ProcessingCore::cmdInfo(SOCKET fdSock, char *cmd)
{
  return true;
}

bool			 ProcessingCore::cmdQuit(SOCKET fdSock, char *cmd)
{
  return true;  
}

bool			 ProcessingCore::cmdEnd(SOCKET fdSock, char *cmd)
{
  return true;    
}
