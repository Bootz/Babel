//
// AudioData.cpp for Babel in /Users/yannkoeth/scm/Babel/client/src
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Nov 25 14:40:43 2011 koeth_y
// Last update Fri Nov 25 14:40:59 2011 koeth_y
//

#include "AudioData.hpp"
#include <iostream>

AudioData::AudioData(double sampleRate, short channelCount, long msecDuration)
  : _data(NULL), _sampleRate(sampleRate), _channelCount(channelCount), _msecDuration(msecDuration)
{
  int totalFrames;
  int sampleCount;
  int bytesCount;

  totalFrames = msecDuration / 1000.0 * sampleRate;
  sampleCount = totalFrames * channelCount;
  bytesCount = sampleCount * sizeof(AudioData::Sample);

  this->_data = static_cast<AudioData::Sample*>(operator new(bytesCount));
  for (int i = 0; i < sampleCount; ++i)
    this->_data[i] = 0;
}

AudioData::~AudioData()
{
  delete _data;
}

long AudioData::getDuration() const
{
  return this->_msecDuration;
}

AudioData::Sample* AudioData::operator[](unsigned long i) const
{
  return &this->_data[i];
}
