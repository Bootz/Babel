//
// IThread.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/thread
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:55:54 2011 koeth_y
// Last update Fri Dec  2 12:56:29 2011 koeth_y
//

#include "IThread.hpp"

IThread::Exception::Exception(const char* what) throw()
  : _what(what)
{
}

IThread::Exception::~Exception() throw()
{
}

const char* IThread::Exception::what() const throw()
{
  return this->_what;
}
