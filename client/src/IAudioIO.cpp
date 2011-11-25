//
// IAudioIO.cpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Nov 25 11:05:38 2011 koeth_y
// Last update Fri Nov 25 11:06:19 2011 koeth_y
//

#include "IAudioIO.hpp"

IAudioIO::Exception::Exception(const char* what)
  : _what(what)
{
}

const char* IAudioIO::Exception::what() const throw()
{
  return this->_what;
}
