//
// main.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/thread
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:20:08 2011 koeth_y
// Last update Sun Dec  4 14:40:15 2011 koeth_y
//

#include <iostream>

#if defined (_WIN32) || defined (WIN32)
# include "WThread.hpp"
typedef WThread Thread;
# define msleep(X) Sleep(X)
#else // UNIX
# include "UThread.hpp"	
typedef UThread Thread;
# define msleep(X) usleep((X) * 1000);
#endif

class Toto
{
private:
  static void* threadCallback(void* arg);

public:
  bool quit;
  Toto();
  void loop();
};

Toto::Toto()
  : quit(false)
{
}

void* Toto::threadCallback(void* arg)
{
  std::cout << std::endl << "thread start" << std::endl;
  bool* quit = static_cast<bool*>(arg);
  while (!*quit)
    {
      std::cout << "thread running" << std::endl;
      msleep(1000);
    }
  quit = false;
  std::cout << "thread end" << std::endl;

  return 0;
}

void Toto::loop()
{
  IThread* thread = new Thread;
  IThread::ThreadRoutine callback = &Toto::threadCallback;
  thread->run(callback, &this->quit);
}

int main(void)
{
  try
    {
      char quit = 0;
      Toto toto;

      toto.loop();
      while (quit != 'y' && quit != 'n')
	{
	  std::cout << "Quit (y or n + <enter>) > ";
	  std::cin >> quit;
	  std::cout << "Your choice : " << quit << std::endl;
	  if (quit == 'y')
	    toto.quit = true;
	}
      std::cout << "main loop" << std::endl;
      while (true)
		msleep(100);
    }
  catch (const IThread::Exception& e)
    {
      std::cerr << "Thread error: " << e.what() << std::endl; 
  }
  return 0;
}
