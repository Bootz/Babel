//
// WThread.cpp for Babel in /Users/yannkoeth/scm/Babel/client/src
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:45:41 2011 koeth_y
// Last update Fri Dec  2 19:24:40 2011 koeth_y
//

#include <cstring>
#include "WThread.hpp"

WThread::WThread()
{
}

WThread::~WThread()
{
}

void	WThread::run(IThread::ThreadRoutine start, void *arg)
{
  if ((this->_threadHandle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(start), arg, 0, 
	  &this->_threadID)) == NULL)
		throw (IThread::Exception("Error creating thread"));
}

void	WThread::wait(void** returnValue)
{
	WaitForSingleObject(this->_threadHandle, INFINITE);
	DWORD exitCode;
	GetExitCodeThread(this->_threadHandle, &exitCode);
	if (exitCode && returnValue)
		*returnValue = reinterpret_cast<void*>(exitCode);
}

void	WThread::exit(void* status)
{
	if (this->_threadHandle)
		ExitThread(reinterpret_cast<DWORD>(status));
}
