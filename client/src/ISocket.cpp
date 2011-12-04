//
// ISocket.cpp for Babel in /home/xsyann/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 20:10:50 2011 koeth_y
// Last update Sun Dec  4 20:11:17 2011 koeth_y
//

#include "ISocket.hpp"

ISocket::Exception::Exception(const char* what) throw()
  : _what(what)
{
}

ISocket::Exception::~Exception() throw()
{
}

const char* ISocket::Exception::what() const throw()
{
  return this->_what;
}
