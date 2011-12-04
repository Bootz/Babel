//
// AudioData.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Nov 25 14:39:19 2011 koeth_y
// Last update Sun Dec  4 22:56:12 2011 koeth_y
//

#ifndef		__AUDIO_DATA_HPP__
#define		__AUDIO_DATA_HPP__

#include <cstring>

class AudioData
{
public:
  typedef float Sample;

private:
  AudioData::Sample* _data;
  double _sampleRate;
  short _channelCount;
  long _msecDuration;
  size_t _size;

public:
  AudioData();
  AudioData(double sampleRate, short channelCount, long msecDuration);
  AudioData(const AudioData&);
  AudioData& operator=(const AudioData&);
  ~AudioData();

  long getDuration() const; // in milliseconds
  void setDuration(long msec);

  const AudioData::Sample* getData() const;
  void setData(AudioData::Sample*);
  size_t getSize() const;

  AudioData::Sample* operator[](unsigned long i) const;
};

#endif		// __AUDIO_DATA_HPP__
