
#include		"processingCore.hh"

// ProcessingCore::ProcessingCore()
// {

// }

ProcessingCore::ProcessingCore(short unsigned int nb_client)
  : _nbClient(nb_client)
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

  i = 0;
  sock = this->_sock->clientAccept(fdSock);
  this->_sock->recv_d(sock, this->_buffer);
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
  this->_clientsManager->add(name, password, "192.168.1.1", sock);
  this->_nbClient++;
}

bool			ProcessingCore::extractCommand(std::string & command)
{
  int			i;

  i = 0;
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

void			ProcessingCore::setSocket(ISocket *sock)
{
  this->_sock = sock;
}

void			ProcessingCore::setClientmanager(clientManager *clientmanager)
{
  this->_clientsManager = clientmanager;
}

void			ProcessingCore::setNbClient(unsigned short nbclient)
{
  this->_nbClient = nbclient;
}
