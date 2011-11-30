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
  : serverSocket(new servSocket()),
    clientmanager(*serverSocket),
    nbClient(0),
    proced(*serverSocket, clientmanager, nbClient),
    running(true)
{
  if (this->serverSocket->connectToServer("INADDR_ANY", 42420) == false)
    throw BabelException("[ERROR] Bad network init");
  this->buffer = new char [1024];
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
      FD_SET(fd, &this->fdread);
      if (fd > this->nbClient)
	this->nbClient = fd;
    }
  if (fd < 0)
    {
      FD_CLR(-fd, &this->fdread);
      i = this->nbClient;
      while (i && !FD_ISSET(i, &this->fdread))
	i--;
    }
}

bool Server::main_loop(void)
{
  while (this->running)
    {
      if (select(this->nbClient + 1, &this->fdread, &this->fdwrite, NULL, NULL) == -1)
	throw BabelException("[ERROR] can't perform select");
      for (int i = 0; i < this->nbClient; ++i)
	if (FD_ISSET(i, &this->fdread))		//Selection of writing clients
	  {
	    if (this->clientmanager.isInList(i))
	      {
		this->serverSocket->recv_d(this->clientmanager.getSocket(i), this->buffer);
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

