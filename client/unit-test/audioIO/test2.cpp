//
// test2.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Dec  2 18:43:25 2011 koeth_y
// Last update Fri Dec  2 22:26:28 2011 koeth_y
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
      while (i < 200)
	{
	  if (data1)
	    {
	      audioIO1->startPlay(*data1);
	      //std::cout << "start play 1" << std::endl;
	    }
	  //std::cout << "start record" << std::endl;
	  audioIO->startRecord(200); // 1000 ms
	  AudioData* data = audioIO->getRecorded();
	  //std::cout << "start play" << std::endl;
	  audioIO->startPlay(*data);
	  //std::cout << "start record 1" << std::endl;
	  audioIO1->startRecord(200); // 1000 ms
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
