/***********************************************************************
 * Module:  Server.cpp
 * Author:  Sioul
 * Modified: mercredi 16 novembre 2011 20:39:23
 * Purpose: Implementation of the class Server
 ***********************************************************************/

#include "Server.hpp"
#include "Exception.hpp"

Server Server::onlyInstance = Server();

#ifdef WIN32
typedef WSocket servSocket;
#else							//unix
typedef LSocket servSocket;
#endif


Server::Server()
  : _serverSocket(new servSocket()),
    _clientmanager(*_serverSocket),
    _nbClient(0),
    _proced(*_serverSocket, _clientmanager, _nbClient),
    _running(true)
{
  if (this->_serverSocket->connectToServer("INADDR_ANY", 42420) == false)
    throw BabelException("[ERROR] Bad network init");
  this->_buffer = new char [1024];
}

Server::~Server()
{
   // TODO : implement
}

Server &Server::getInstance()
{
  return onlyInstance;
}

void			Server::setFd(const int fd)
{
  int			i = 0;

  if (fd > 0)
    {
      FD_SET(fd, &this->_fdread);
      if (fd > this->_nbClient)
	this->_nbClient = fd;
    }
  if (fd < 0)
    {
      FD_CLR(-fd, &this->_fdread);
      i = this->_nbClient;
      while (i && !FD_ISSET(i, &this->_fdread))
	i--;
    }
}

bool Server::main_loop(void)
{
  while (this->_running)
    {
      if (select(this->_nbClient + 1, &this->_fdread, &this->_fdwrite, NULL, NULL) == -1)
	throw BabelException("[ERROR] can't perform select");
      for (int i = 0; i < this->_nbClient; ++i)
	if (FD_ISSET(i, &this->_fdread))		//Selection of writing clients
	  {
	    if (this->_clientmanager.isInList(i))
	      {
		this->_serverSocket->recv_d(this->_clientmanager.getSocket(i), this->_buffer);
		//pointeur sur fonction		//send to processing core
	      }
	  }
    }
  return true;
}

bool			Server::connectClients(ServerClient& caller, std::string name)
{
  (void) caller;
  (void) name;
  return true;  
}

