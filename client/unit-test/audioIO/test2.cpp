//
// test2.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 18:43:25 2011 koeth_y
// Last update Sun Dec  4 14:37:33 2011 koeth_y
//

#include <iostream>
#include "PortAudio.hpp"

int main(void)
{
  try
    {
      int i = 0;
      AudioData* data1 = NULL;
      IAudioIO* audioIO = new PortAudio;
      IAudioIO* audioIO1 = new PortAudio;
      while (i < 50)
	{
	  if (data1)
	    {
	      audioIO1->startPlay(*data1);
	    }
	  audioIO->startRecord(600);
	  AudioData* data = audioIO->getRecorded();
	  audioIO->startPlay(*data);
	  audioIO1->startRecord(600);
	  if (data1)
	    delete data1;
	  data1 = audioIO1->getRecorded();
	  delete data;
	  ++i;
	}
      std::cout << "end loop"<< std::endl;
      delete audioIO;
      delete audioIO1;
      std::cout << "end deleting"<< std::endl;
    }
  catch (const IAudioIO::Exception& e)
    {
      std::cerr << "Babel error: " << e.what() << std::endl;
    }
  std::cout << "end prog"<< std::endl;
  return 0;
}
