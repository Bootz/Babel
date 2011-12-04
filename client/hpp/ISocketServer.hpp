//
// ISocketServer.hpp for Babel in /home/xsyann/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 20:27:08 2011 koeth_y
// Last update Sun Dec  4 22:13:46 2011 koeth_y
//

#ifndef		__ISOCKET_SERVER_HPP__
#define		__ISOCKET_SERVER_HPP__

#include <string>

class ISocketServer
{
public:
  typedef void (*ServerCallback)(void* data);
public:
  virtual ~ISocketServer() {}

  virtual bool run(ServerCallback callback, const std::string& ip = "127.0.0.1", short port = 4242) = 0;
};

#endif		// __ISOCKET_SERVER_HPP__
