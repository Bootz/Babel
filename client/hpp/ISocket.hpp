//
// ISocket.hpp for Babel in /home/xsyann/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 20:05:14 2011 koeth_y
// Last update Sun Dec  4 21:43:57 2011 koeth_y
//

#ifndef		__ISOCKET_HPP__
#define		__ISOCKET_HPP__

#include <string>

class ISocket
{
public:
  virtual bool run(const std::string& ip = "127.0.0.1", short port = 4242) = 0;

  virtual void* receive() = 0;
  virtual bool send(const void*, size_t) = 0;

  virtual bool isConnected() const = 0;

  virtual ~ISocket() {};

public:
  class Exception : public std::exception
  {
    const char* _what;
  public:
    Exception() throw();
    Exception(const char* what) throw();
    Exception(const Exception&) throw();
    Exception& operator=(const Exception&) throw();
    virtual ~Exception() throw();
    virtual const char* what() const throw();
  };
};

#endif		// __ISOCKET_HPP__
