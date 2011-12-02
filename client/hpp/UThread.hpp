//
// UThread.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:38:39 2011 koeth_y
// Last update Fri Dec  2 19:24:59 2011 koeth_y
//

#ifndef		__UTHREAD_HPP__
#define		__UTHREAD_HPP__

#include <pthread.h>
#include "IThread.hpp"

class UThread : public IThread
{
private:
  pthread_t _thread;

public:
  UThread();
  UThread(const UThread&);
  UThread& operator=(const UThread&);
  virtual ~UThread();

  virtual void run(IThread::ThreadRoutine start, void* arg = NULL);
  virtual void wait(void** returnValue = NULL);
  virtual void exit(void* status = NULL);
};

#endif		// __UTHREAD_HPP__
