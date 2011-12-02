//
// main.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/thread
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 12:20:08 2011 koeth_y
// Last update Fri Dec  2 20:20:21 2011 koeth_y
//

#include <iostream>
#include "UThread.hpp"

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
      usleep(1000000);
    }
  quit = false;
  std::cout << "thread end" << std::endl;

  return NULL;
}

void Toto::loop()
{
  IThread* thread = new UThread;
  IThread::ThreadRoutine callback = &Toto::threadCallback;
  thread->run(callback, &quit);
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
	  std::cout << "Quit (y or n) > ";
	  std::cin >> quit;
	  std::cout << "Your choice : " << quit << std::endl;
	  if (quit == 'y')
	    toto.quit = true;
	}
      std::cout << "main loop" << std::endl;
      while (true)
	usleep(1000);
    }
  catch (const IThread::Exception& e)
    {
      std::cerr << "Thread error: " << e.what() << std::endl;
    }
  return 0;
}
