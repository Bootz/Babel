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
  if (this->_serverSocket->initServer(42420) == false)
    throw BabelException("[ERROR] Bad network init");
  this->_buffer = new char [1024];
  FD_SET(this->_serverSocket->getListenSocket(), &this->_master);
}

Server::~Server()
{
  this->_serverSocket->closeSocket();
}

Server &Server::getInstance()
{
  return onlyInstance;
}

void			Server::setFd(const int fd)
{
  this->_tv.tv_sec = 1;
  this->_tv.tv_usec = 0;
  FD_ZERO(&this->_fdread);
  if (this->_clientmanager.isInList(fd))
    FD_SET(fd, &this->_fdread);
  else
    this->_fdread = this->_master;
}

bool Server::main_loop(void)
{
  std::cout << "[main_loop] begin" << std::endl;

  while (this->_running)
    {
      for (int i = 0; i < 1023 + 1; ++i)
	{
	  this->setFd(i);
	  if (select(i + 1, &this->_fdread, NULL, NULL, &this->_tv) == -1)
	    throw BabelException("[ERROR] can't perform select");
	  for (int j = 0; j < 1023 + 1; ++j)
	    {
	      if (FD_ISSET(j, &this->_fdread))
		{
		  if (this->_clientmanager.isInList(j))
		    this->_serverSocket->recv_d(this->_clientmanager.getSocket(j), this->_buffer);
		  else
		    {
		      if (!this->_clientmanager.isInList(j))
			{
			  this->_nbClient = this->_serverSocket->clientAccept(j);
			  FD_SET(this->_nbClient, &this->_master);
			  this->_clientmanager.createClient(this->_nbClient);
			  std::cout << "[main_loop] The client [" << j << "] has been add" << std::endl;
			  std::cout << "IP: " << this->_serverSocket->getIp() << std::endl;
			}
		    }
		}
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

