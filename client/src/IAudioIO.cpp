//
// IAudioIO.cpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Nov 25 11:05:38 2011 koeth_y
// Last update Mon Nov 28 13:07:47 2011 koeth_y
//

#include "IAudioIO.hpp"

IAudioIO::Exception::Exception(const char* what) throw()
  : _what(what)
{
}

IAudioIO::Exception::~Exception() throw()
{
}

const char* IAudioIO::Exception::what() const throw()
{
  return this->_what;
}
