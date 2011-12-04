//
// Socket.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 17:00:35 2011 koeth_y
// Last update Sun Dec  4 21:44:01 2011 koeth_y
//

#ifndef		__SOCKET_HPP__
#define		__SOCKET_HPP__

#include <string>
#include <QTcpSocket>
#include "ISocket.hpp"

class Socket : public ISocket
{
private:
  QTcpSocket* _client;

  static const int DELTA = 200;
  int _waitClient();

  friend class SocketServer;
 
public:
  Socket();
  Socket(const Socket&);
  Socket& operator=(const Socket&);
  virtual ~Socket();

  virtual bool run(const std::string& ip = "127.0.0.1", short port = 4242);
  virtual void* receive();
  virtual bool send(const void*, size_t);
  virtual bool isConnected() const;
};

#endif		// __SOCKET_HPP__
