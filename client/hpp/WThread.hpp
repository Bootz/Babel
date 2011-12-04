//
// WThread.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:38:39 2011 koeth_y
// Last update Fri Dec  2 19:24:59 2011 koeth_y
//

#ifndef		__WTHREAD_HPP__
#define		__WTHREAD_HPP__

#include <windows.h>
#include "IThread.hpp"

class WThread : public IThread
{
private:
  DWORD _threadID;
  HANDLE _threadHandle;

public:
  WThread();
  WThread(const WThread&);
  WThread& operator=(const WThread&);
  virtual ~WThread();

  virtual void run(IThread::ThreadRoutine start, void* arg = NULL);
  virtual void wait(void** returnValue = NULL);
  virtual void exit(void* status = NULL);
};

#endif		// __WTHREAD_HPP__
