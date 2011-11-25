//
// PortAudio.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Thu Nov 24 13:24:53 2011 koeth_y
// Last update Fri Nov 25 14:49:07 2011 koeth_y
//

#ifndef		__PORT_AUDIO_HPP__
#define		__PORT_AUDIO_HPP__

#include <string>
#include "portaudio.h"
#include "IAudioIO.hpp"

class PortAudio : public IAudioIO
{
private:
  static const double SAMPLE_RATE = 44100.0;
  static const unsigned long FRAMES_PER_BUFFER = 512;
  static const short CHANNEL_COUNT = 2;
  static const short DITHER_FLAG = 0;
  static const PaSampleFormat SAMPLE_TYPE = paFloat32;
  static const AudioData::Sample SAMPLE_SILENCE = 0.0f;

  struct Data
  {
    int frameIndex;
    int maxFrameIndex;
    AudioData *recordedData;
    const AudioData *data;
  };

private:
  inline const PaError& handleError(const PaError&) const;
  inline void handleError(const std::string&) const;

  // Callbacks
  static int recordCallback(const void *inputBuffer, void *outputBuffer,
		      unsigned long framesPerBuffer,
		      const PaStreamCallbackTimeInfo* timeInfo,
		      PaStreamCallbackFlags statusFlags,
	       void *userData);
  static int playCallback(const void *inputBuffer, void *outputBuffer,
		      unsigned long framesPerBuffer,
		      const PaStreamCallbackTimeInfo* timeInfo,
		      PaStreamCallbackFlags statusFlags,
	       void *userData);

public:
  PortAudio();
  
  PortAudio(const PortAudio&);
  PortAudio& operator=(const PortAudio&);
  virtual ~PortAudio();

  virtual AudioData* record(long msec);
  virtual void play(const AudioData*) const;
};

#endif		// __PORT_AUDIO_HPP__
