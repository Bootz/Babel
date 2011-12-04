//
// test1.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 18:43:25 2011 koeth_y
// Last update Sun Dec  4 14:36:43 2011 koeth_y
//

#include <iostream>
#include "PortAudio.hpp"

#if defined (_WIN32) || defined (WIN32)
# include <windows.h>
# define msleep(X) Sleep(X)
#else // UNIX
# define msleep(X) usleep((X) / 1000)
#endif

int main(void)
{
  try
    {
      IAudioIO* audioIO = new PortAudio;

      std::cout << "Start record (9 s)" << std::endl;

      audioIO->startRecord(9000); // 9000 ms == 9 s

      int i = 0;
      while (audioIO->isRecording())
	{
	  if (i == 6) // stop at 6 s
	    audioIO->stopRecord();

	  std::cout << "Recording... ~ " << i << " s (stop at 6)" << std::endl;
	  msleep(1000);
	  ++i;
	}
      AudioData* data = audioIO->getRecorded();
      audioIO->startPlay(*data);
      int j = 0;
      while (audioIO->isPlaying())
	{
	  if (j == 3) // stop at 3 s
	    audioIO->stopPlay();

	  std::cout << "Playing... ~ " << j << " s (stop at 3)" << std::endl;
	  msleep(1000);
	  ++j;
	}
      delete data;
      delete audioIO; 
    }
  catch (const IAudioIO::Exception& e)
    {
      std::cerr << "Babel error: " << e.what() << std::endl;
    }
  return 0;
}
