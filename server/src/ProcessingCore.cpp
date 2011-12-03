
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
  Protocol *protocol = static_cast<Protocol *>(cmd);
   
    if (static_cast<size_t> (protocol->cmd) <= this->_command.size())
      return (this->*this->_command[protocol->cmd])(sock, *protocol);
    return false;
 }

void readProtocol(SOCKET, void * cmd)
{
  Protocol *protocol = static_cast<Protocol *>(cmd);

  if (protocol->cmd == CL_REGISTER) // todo : pointers array
    {
      const RegisterParam* registerParam = static_cast<const RegisterParam*>(protocol->data);
      std::cout << "login = " << registerParam->login << " password = " << registerParam->password << std::endl;
      delete registerParam;
    }
  else if (protocol->cmd == CL_INFO)
    {
      const InfoParam* infoParam = static_cast<const InfoParam*>(protocol->data);
      size_t loginsOffset = sizeof(*infoParam) - sizeof(infoParam->logins);
      for (int unsigned i = 0; i < infoParam->clientCount; ++i)
	{
	  char* currentLogin = static_cast<char*>(protocol->data) + loginsOffset + LEN_NAME * i;
	  std::cout << currentLogin << std::endl;
	}
      delete infoParam;
    }
}


bool			 ProcessingCore::cmdRegister(SOCKET fdSock, __attribute__ ((unused))Protocol proto)
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

bool			 ProcessingCore::cmdLogin(SOCKET fdSock, Protocol proto)
{
  return true;  
}

bool			 ProcessingCore::cmdInfo(SOCKET fdSock, Protocol proto)
{
  return true;
}

bool			 ProcessingCore::cmdQuit(SOCKET fdSock, Protocol proto)
{
  return true;  
}

bool			 ProcessingCore::cmdEnd(SOCKET fdSock, Protocol proto)
{
  return true;    
}
