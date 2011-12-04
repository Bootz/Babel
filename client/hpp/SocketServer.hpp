//
// SocketServer.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 17:01:20 2011 koeth_y
// Last update Sun Dec  4 22:13:14 2011 koeth_y
//

#ifndef		__SOCKET_SERVER_HPP__
#define		__SOCKET_SERVER_HPP__

#include <string>
#include "ISocketServer.hpp"

class QTcpServer;
class Socket;

class SocketServer : public ISocketServer
{
private:

  static const int DELTA = 200;

  QTcpServer* _server;
  Socket* _client;
 
public:
  SocketServer();
  SocketServer(const SocketServer&);
  SocketServer& operator=(const SocketServer&);
  virtual ~SocketServer();

  virtual bool run(ISocketServer::ServerCallback callback, const std::string& ip = "127.0.0.1", short port = 4242);
};

#endif		// __SOCKET_SERVER_HPP__
