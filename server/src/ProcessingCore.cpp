
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
  std::pair<int, fct>   tmp(1, &ProcessingCore::cmdRegister);
  this->_command.push_back(tmp);
}

bool ProcessingCore::cmdRegister(SOCKET fdSock, char *cmd)
{
  std::string		password;
  unsigned short	sock;
  std::string		name;
  std::string		buf;
  int			pos;
  int			i;

  (void) cmd;
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
  this->_nbClient++;
  return true;
}

 bool			ProcessingCore::extractCommand(void *cmd)
 {
   t_babelProtcol *tmp = reinterpret_cast<t_babelProtcol *>(cmd);
   size_t test =  tmp->getSize();
  
   return true;
 }
