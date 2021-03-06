/***********************************************************************
 * Module:  Server.cpp
 * Author:  Sioul
 * Modified: mercredi 16 novembre 2011 20:39:23
 * Purpose: Implementation of the class Server
 ***********************************************************************/

#include "Server.hpp"
#include "BabelException.hpp"

Server Server::onlyInstance = Server();

#ifdef WIN32
typedef WSocket servSocket;
#else							//unix
typedef LSocket servSocket;
#endif


Server::Server()
  : _serverSocket(new servSocket()),
    _clientmanager(*_serverSocket),
    _proced(*_serverSocket, _clientmanager, _nbClient),
    _running(true)
{
  std::cout << "Creation du serveur." << std::endl;
  this->_buffer = new char [8192];
  if (this->_serverSocket->initServer(42420) == false)
    throw BabelException("[ERROR] Bad network init");
  FD_ZERO(&this->_master);
  FD_SET(this->_serverSocket->getListenSocket(), &this->_master);
  this->_nbClient = this->_serverSocket->getListenSocket();
}

Server::~Server()
{
  delete this->_buffer;
  this->_serverSocket->closeSocket();
  delete this->_serverSocket;
}

Server &Server::getInstance()
{
  return onlyInstance;
}

void			Server::setFd()
{
  this->_tv.tv_sec = 1;
  this->_tv.tv_usec = 0;
  FD_ZERO(&this->_fdread);
  this->_fdread = this->_master;
}

bool Server::main_loop(void)
{
  std::cout << "Lancement de la main loop du serveur." << std::endl;
  while (this->_running)
    {
      this->setFd();
      if (select(this->_nbClient + 1, &this->_fdread, NULL, NULL, &this->_tv) == -1)
	throw BabelException("[ERROR] can't perform select");
      for (int j = 0; j < this->_nbClient + 1; ++j)
	{
	  if (FD_ISSET(j, &this->_fdread))
	    {
	      if (j == this->_serverSocket->getListenSocket())
		{
		  this->_nbClient = this->_serverSocket->clientAccept(j);
		  FD_SET(this->_nbClient, &this->_master);
		  this->_clientmanager.createClient(this->_nbClient);
		}
	      else
		{
		  if ((this->_serverSocket->recv_d(j, this->_buffer)) == 0)
		    {
		      FD_CLR(j, &this->_master);
		      this->_clientmanager.delClient(j);
		      close(j);
		    }
		  else
		    this->_proced.commandChoice(j, this->_buffer);
		}
	    }
	}
    }
  return true;
}

bool			Server::connectClients(ServerClient& caller, const std::string & name)
{
  (void) caller;
  (void) name;
  return true;
}

