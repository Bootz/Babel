//
// UThread.cpp for Babel in /Users/yannkoeth/scm/Babel/client/src
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:45:41 2011 koeth_y
// Last update Fri Dec  2 19:24:40 2011 koeth_y
//

#include <cstring>
#include "UThread.hpp"

UThread::UThread()
{
}

UThread::~UThread()
{
}

void	UThread::run(IThread::ThreadRoutine start, void *arg)
{
  int	error;

  if ((error = pthread_create(&this->_thread, NULL, start, arg)))
    throw (IThread::Exception(strerror(error)));
}

void	UThread::wait(void** returnValue)
{
  int	error;

  if ((error = pthread_join(this->_thread, returnValue)))
    throw (IThread::Exception(strerror(error)));
}

void	UThread::exit(void* status)
{
  pthread_exit(status);
}
