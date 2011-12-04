//
// SocketServer.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 17:11:24 2011 koeth_y
// Last update Sun Dec  4 22:20:45 2011 koeth_y
//

#include <iostream>
#include <QtNetwork>
#include <QTcpServer>
#include "Socket.hpp"
#include "SocketServer.hpp"

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
# define msleep(X) Sleep(X)
#else // UNIX
# define msleep(X) usleep((X) * 1000)
#endif

SocketServer::SocketServer()
{
  this->_server = new QTcpServer();
  this->_client = new Socket();
}

bool SocketServer::run(ServerCallback callback, const std::string& ip, short port)
{
  QHostAddress host(ip.c_str());

  if (!_server->listen(host, port))
    throw ISocket::Exception("Unable to start the server");
  while (_server->isListening())
    {
      if (_server->waitForNewConnection(200))
	{
	  _client->_client = _server->nextPendingConnection();
	  char* data;
	  std::string line;
	  do {
	    data = static_cast<char*>(this->_client->receive());
	    if (data)
	      line = data;
	    else
	      line = "";
	    
	    if (line.length() > 0)
	      callback(data);
	  } while (line.length() > 0);
	}
      else
	msleep(SocketServer::DELTA);
    }
  return true;
}

SocketServer::~SocketServer()
{
  delete this->_client;
  delete this->_server;
}
