//
// PortAudio.cpp for Babel in /Users/yannkoeth/scm/Babel/client/src
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Thu Nov 24 13:28:48 2011 koeth_y
// Last update Fri Dec  2 21:11:57 2011 koeth_y
//

#include "UThread.hpp"
#include "PortAudio.hpp"

inline const PaError& PortAudio::handleError(const PaError& error) const
{
 if (error != paNoError)
    {
      throw IAudioIO::Exception(Pa_GetErrorText(error));
      Pa_Terminate();
    }
 return error;
}

inline void PortAudio::throwError(const std::string& s) const
{
  throw IAudioIO::Exception(s.c_str());
  Pa_Terminate();
}

PortAudio::PortAudio()
  : _stopRecord(false), _isRecording(false), _stopPlay(false), _isPlaying(false),
    _recordThread(new UThread), _playThread(new UThread)
{
  handleError(Pa_Initialize());
}

int PortAudio::recordCallback(const void *inputBuffer, void *outputBuffer,
		      unsigned long framesPerBuffer,
		      const PaStreamCallbackTimeInfo* timeInfo,
		      PaStreamCallbackFlags statusFlags,
		      void *userData)
{
  PortAudio::Data* data = static_cast<Data*>(userData);
  const AudioData::Sample* readPtr = static_cast<const AudioData::Sample*>(inputBuffer);
  AudioData::Sample* writePtr = (*data->recordedData)[data->frameIndex * PortAudio::CHANNEL_COUNT];
  long framesToCalculate;
  int finished;
  unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
  
  (void) outputBuffer;
  (void) timeInfo;
  (void) statusFlags;

  if (framesLeft < framesPerBuffer)
    {
      framesToCalculate = framesLeft;
      finished = paComplete;
    }
  else
    {
      framesToCalculate = framesPerBuffer;
      finished = paContinue;
    }
  if (inputBuffer == NULL)
    {
      for (long i = 0; i < framesToCalculate; ++i)
	{
	  *writePtr++ = PortAudio::SAMPLE_SILENCE;
	  if (PortAudio::CHANNEL_COUNT == 2)
	    *writePtr++ = PortAudio::SAMPLE_SILENCE;
	}
    }
  else
    {
      for (long i = 0; i < framesToCalculate; ++i)
	{
	  *writePtr++ = *readPtr++;
	  if (PortAudio::CHANNEL_COUNT == 2)
	    *writePtr++ = *readPtr++;
	}
    }
  data->frameIndex += framesToCalculate;
  return finished;
}

int PortAudio::playCallback(const void *inputBuffer, void *outputBuffer,
		      unsigned long framesPerBuffer,
		      const PaStreamCallbackTimeInfo* timeInfo,
		      PaStreamCallbackFlags statusFlags,
		      void *userData)
{
  PortAudio::Data* data = static_cast<Data*>(userData);
  const AudioData& audioData = *data->data;
  const AudioData::Sample* readPtr = audioData[data->frameIndex * PortAudio::CHANNEL_COUNT];
  AudioData::Sample* writePtr = static_cast<AudioData::Sample*>(outputBuffer);
  int finished;
  unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
  
  (void) inputBuffer;
  (void) timeInfo;
  (void) statusFlags;

  if (framesLeft < framesPerBuffer)
    {
      unsigned long i;
      for (i = 0; i < framesLeft; ++i)
	{
	  *writePtr++ = *readPtr++;
	  if (PortAudio::CHANNEL_COUNT == 2)
	    *writePtr++ = *readPtr++;
	}
      for ( ; i < framesPerBuffer; ++i)
	{
	  *writePtr++ = 0;
	  if (PortAudio::CHANNEL_COUNT == 2)
	    *writePtr++ = 0;
	}
      data->frameIndex += framesLeft;
      finished = paComplete;
    }
  else
    {
      for (unsigned long i = 0; i < framesPerBuffer; ++i)
	{
	  *writePtr++ = *readPtr++;
	  if (PortAudio::CHANNEL_COUNT == 2)
	    *writePtr++ = *readPtr++;
	}
      data->frameIndex += framesPerBuffer;
      finished = paContinue;
    }
  return finished;
}

void PortAudio::startRecord(long msec)
{
  this->_stopRecord = false;
  this->_isRecording = true;
  IThread::ThreadRoutine callback = PortAudio::recordThread;
  PortAudio::RecordParameters* recordParameters =  new PortAudio::RecordParameters;
  recordParameters->msec = msec;
  recordParameters->self = this;
  try
    {
      this->_recordThread->run(callback, recordParameters);
    }
  catch (const IThread::Exception& e)
    {
      throw IAudioIO::Exception(e.what());
    }
}

void PortAudio::stopRecord()
{
  this->_stopRecord = true;
}

AudioData* PortAudio::getRecorded()
{
  void* recorded;
  try
    {
      this->_recordThread->wait(&recorded);
    }
  catch (const IThread::Exception& e)
    {
      throw IAudioIO::Exception(e.what());
    }
  return static_cast<AudioData*>(recorded);
}

bool PortAudio::isRecording() const
{
  return this->_isRecording;
}

void PortAudio::startPlay(const AudioData& data)
{
  this->_stopPlay = false;
  this->_isPlaying = true;
  IThread::ThreadRoutine callback = PortAudio::playThread;
  PortAudio::PlayParameters* playParameters =  new PortAudio::PlayParameters;
  playParameters->data = &data;
  playParameters->self = this;
  try
    {
      this->_recordThread->run(callback, playParameters);
    }
  catch (const IThread::Exception& e)
    {
      throw IAudioIO::Exception(e.what());
    }
}

void PortAudio::stopPlay()
{
  this->_stopPlay = true;
}

bool PortAudio::isPlaying() const
{
  return this->_isPlaying;
}

void* PortAudio::recordThread(void* arg)
{
  PaStream* stream;
  PaStreamParameters inputParameters;
  PortAudio::Data data;
  PortAudio::RecordParameters* recordParameters = static_cast<PortAudio::RecordParameters*>(arg);
  long msec = recordParameters->msec;
  PortAudio& self = *recordParameters->self;
  delete recordParameters;

  self._isRecording = true;

  data.maxFrameIndex = msec / 1000.0 * PortAudio::SAMPLE_RATE;
  data.frameIndex = 0;
  data.recordedData = new AudioData(PortAudio::SAMPLE_RATE, PortAudio::CHANNEL_COUNT, msec);

  inputParameters.device = Pa_GetDefaultInputDevice();
  if (inputParameters.device == paNoDevice)
    self.throwError("No default input device.");
  inputParameters.channelCount = PortAudio::CHANNEL_COUNT;
  inputParameters.sampleFormat = PortAudio::SAMPLE_TYPE;
  inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
  inputParameters.hostApiSpecificStreamInfo = NULL;

  PaStreamCallback* recordCallback = &PortAudio::recordCallback;

  self.handleError(Pa_OpenStream(&stream,
			    &inputParameters,
			    NULL,
			    PortAudio::SAMPLE_RATE,
			    PortAudio::FRAMES_PER_BUFFER,
			    paClipOff,
			    recordCallback,
			    &data));
  self.handleError(Pa_StartStream(stream));
  PaError error;
  long duration;
  for (duration = 0; (error = Pa_IsStreamActive(stream)) == 1 && !self._stopRecord; duration += 10)
    Pa_Sleep(10);
  if (duration < data.recordedData->getDuration())
    data.recordedData->setDuration(duration);
  if (error < 0)
    self.handleError(error);
  self.handleError(Pa_CloseStream(stream));

  self._isRecording = false;
  
  self._recordThread->exit(data.recordedData);
  return data.recordedData;
}

void* PortAudio::playThread(void* arg)
{
  PaStream* stream;
  PortAudio::Data data;
  PortAudio::PlayParameters* playParameters = static_cast<PortAudio::PlayParameters*>(arg);
  const AudioData& audioData = *playParameters->data;
  PortAudio& self = *playParameters->self;
  delete playParameters;

  data.maxFrameIndex = audioData.getDuration() / 1000.0 * PortAudio::SAMPLE_RATE;
  data.frameIndex = 0;
  data.data = &audioData;

  self._isPlaying = true;

  PaStreamParameters outputParameters;
  outputParameters.device = Pa_GetDefaultOutputDevice();
  if (outputParameters.device == paNoDevice)
    self.throwError("No default output device.");
  outputParameters.channelCount = PortAudio::CHANNEL_COUNT;
  outputParameters.sampleFormat = PortAudio::SAMPLE_TYPE;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  PaStreamCallback* playCallback = &PortAudio::playCallback;

  self.handleError(Pa_OpenStream(&stream,
			    NULL,
			    &outputParameters,
			    PortAudio::SAMPLE_RATE,
			    PortAudio::FRAMES_PER_BUFFER,
			    paClipOff,
			    playCallback,
			    &data));
  if (stream)
    {
      self.handleError(Pa_StartStream(stream));
      PaError error;
      while ((error = Pa_IsStreamActive(stream)) == 1 && !self._stopPlay)
	  Pa_Sleep(10);
      if (error < 0)
      self.handleError(error);
      self.handleError(Pa_CloseStream(stream));
    }
  self._isPlaying = false;

  self._playThread->exit();
  return NULL;
}

PortAudio::~PortAudio()
{
  this->stopPlay();
  this->stopRecord(); 
  // Be sure threads finished
  try
    {
      this->_recordThread->wait();
    }
  catch (const IThread::Exception& e) {}
  try
    {
      this->_playThread->wait();
    }
  catch (const IThread::Exception& e) {}
  delete this->_recordThread;
  delete this->_playThread;
  Pa_Terminate();
}
