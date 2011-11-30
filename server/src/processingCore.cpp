
#include		"processingCore.hpp"

// ProcessingCore::ProcessingCore()
// {

// }

ProcessingCore::ProcessingCore(ISocket & sock, clientManager & cm, unsigned short& nbclient)
  : _sock(sock),
    _clientsManager(cm),
    _nbClient(nbclient)
{
}

ProcessingCore::~ProcessingCore()
{

}


// void ProcessingCore::initialize()
// {
//   this->_command.push_back(std::pair<std::string, fct>("REGISTER", ProcessingCore::cmdRegister(this->_actSock, this->_buffer)));
// }

bool ProcessingCore::cmdRegister(SOCKET fdSock, std::string cmd)
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
  this->_clientsManager.add(name, password, "192.168.1.1", sock);
  this->_nbClient++;
  return true;
}

bool			ProcessingCore::extractCommand(std::string & command)
{
  size_t		i = 0;

  while (i < this->_command.size())
    {
      if (command.compare(0, this->_command[i].first.size(), this->_command[i].first) == 0)
	{
	  command.assign(command, this->_command[i].first.size() + 1, command.size() -
			 this->_command[i].first.size() + 1);
	  return (/*this->_command[i].*second(command)*/true);
	}
      ++i;
    }
  return (false);
}
