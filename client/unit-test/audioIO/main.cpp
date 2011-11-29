//
// main.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/audioIO
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Thu Nov 24 13:03:26 2011 koeth_y
// Last update Tue Nov 29 15:48:59 2011 koeth_y
//

#include <iostream>
#include "PortAudio.hpp"

static void playAudio(const AudioData* data)
{
  IAudioIO* audioIO = new PortAudio;
  audioIO->play(data);
  delete audioIO;
}

int main(void)
{
  try
    {
      IAudioIO* audioIO = new PortAudio;
      std::cout << "Start record (4 s)" << std::endl;
      AudioData* data = audioIO->record(4000); // 4000 ms == 4 s
      std::cout << "Start play (4 s)" << std::endl;
      // Play twice
      audioIO->play(data);
      std::cout << "Start play 2 (4 s)" << std::endl;
      playAudio(data); // Within a function
      delete data;
      delete audioIO;
    }
  catch (const IAudioIO::Exception& e)
    {
      std::cout << "Babel error: " << e.what() << std::endl;
    }
  return 0;
}
