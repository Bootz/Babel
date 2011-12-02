//
// PortAudio.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Thu Nov 24 13:24:53 2011 koeth_y
// Last update Fri Dec  2 22:27:22 2011 koeth_y
//

#ifndef		__PORT_AUDIO_HPP__
#define		__PORT_AUDIO_HPP__

#include <string>
#include "portaudio.h"
#include "IThread.hpp"
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
  inline void throwError(const std::string&) const;
  
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

  struct RecordParameters
  {
    long msec;
    PortAudio* self;
  };

  struct PlayParameters
  {
    const AudioData* data;
    PortAudio* self;
  };

  bool _stopRecord;
  bool _isRecording;
  bool _stopPlay;
  bool _isPlaying;
  IThread* _recordThread;
  IThread* _playThread;
  static void* recordThread(void* arg);
  static void* playThread(void* arg);

public:
  PortAudio();
  
  PortAudio(const PortAudio&);
  PortAudio& operator=(const PortAudio&);
  virtual ~PortAudio();

  virtual void startRecord(long msec);
  virtual AudioData* getRecorded();
  virtual bool isRecording() const;
  virtual void stopRecord();
  virtual void startPlay(const AudioData&);
  virtual bool isPlaying() const;
  virtual void stopPlay();
};

#endif		// __PORT_AUDIO_HPP__
