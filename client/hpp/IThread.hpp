//
// IThread.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:38:23 2011 koeth_y
// Last update Fri Dec  2 22:17:23 2011 koeth_y
//

#ifndef		__ITHREAD_HPP__
#define		__ITHREAD_HPP__

#include <exception>
#include <iostream>

class IThread
{
public:
  typedef void* (*ThreadRoutine)(void*);

public:
  virtual void run(IThread::ThreadRoutine start, void* arg = NULL) = 0;
  virtual void wait(void** returnValue = NULL) = 0;
  virtual void exit(void* status = NULL) = 0;

  virtual ~IThread() {};

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

#endif		// __ITHREAD_HPP__
