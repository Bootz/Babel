//
// IAudioIO.hpp for Babel in /Users/yannkoeth/scm/Babel/client/hpp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Fri Nov 25 11:01:46 2011 koeth_y
// Last update Fri Dec  2 22:27:19 2011 koeth_y
//

#ifndef		__IAUDIO_IO_HPP__
#define		__IAUDIO_IO_HPP__

#include <exception>
#include "AudioData.hpp"

class IAudioIO
{
public:
  virtual void startRecord(long msec) = 0;
  virtual AudioData* getRecorded() = 0;
  virtual bool isRecording() const = 0;
  virtual void stopRecord() = 0;
  virtual void startPlay(const AudioData&) = 0;
  virtual bool isPlaying() const = 0;
  virtual void stopPlay() = 0;
  virtual ~IAudioIO() {};

public:
  class Exception : public std::exception
  {
    const char* _what;
  public:
    Exception() throw();
    Exception(const char* what) throw();
    Exception(const Exception&) throw();
    Exception& operator=(const Exception&) throw();
    virtual ~Exception() throw();
    virtual const char* what() const throw();
  };

};

#endif		// __IAUDIO_IO_HPP__
