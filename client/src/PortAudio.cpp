//
// PortAudio.cpp for Babel in /Users/yannkoeth/scm/Babel/client/src
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Thu Nov 24 13:28:48 2011 koeth_y
// Last update Fri Nov 25 14:42:07 2011 koeth_y
//

#include "PortAudio.hpp"

inline const PaError& PortAudio::handleError(const PaError& error) const
{
 if (error != paNoError)
    {
      throw new IAudioIO::Exception(Pa_GetErrorText(error));
      Pa_Terminate();
    }
 return error;
}

inline void PortAudio::handleError(const std::string& s) const
{
  throw new IAudioIO::Exception(s.c_str());
  Pa_Terminate();
}

PortAudio::PortAudio()
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

AudioData* PortAudio::record(long msec)
{
  PaStream* stream;
  PaStreamParameters inputParameters;
  PortAudio::Data data;

  data.maxFrameIndex = msec / 1000.0 * PortAudio::SAMPLE_RATE;
  data.frameIndex = 0;
  data.recordedData = new AudioData(PortAudio::SAMPLE_RATE, PortAudio::CHANNEL_COUNT, msec);

  inputParameters.device = Pa_GetDefaultInputDevice();
  if (inputParameters.device == paNoDevice)
    handleError("No default input device.");
  inputParameters.channelCount = PortAudio::CHANNEL_COUNT;
  inputParameters.sampleFormat = PortAudio::SAMPLE_TYPE;
  inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
  inputParameters.hostApiSpecificStreamInfo = NULL;

  PaStreamCallback* recordCallback = &PortAudio::recordCallback;

  handleError(Pa_OpenStream(&stream,
			    &inputParameters,
			    NULL,
			    PortAudio::SAMPLE_RATE,
			    PortAudio::FRAMES_PER_BUFFER,
			    paClipOff,
			    recordCallback,
			    &data));
  handleError(Pa_StartStream(stream));
  PaError error;
  while ((error = Pa_IsStreamActive(stream)) == 1)
    Pa_Sleep(100);
  if (error < 0)
    handleError(error);
  handleError(Pa_CloseStream(stream));

  return data.recordedData;
}

void PortAudio::play(const AudioData* audioData) const
{
  PaStream* stream;
  PortAudio::Data data;

  data.maxFrameIndex = audioData->getDuration() / 1000.0 * PortAudio::SAMPLE_RATE;
  data.frameIndex = 0;
  data.data = audioData;

  PaStreamParameters outputParameters;
  outputParameters.device = Pa_GetDefaultOutputDevice();
  if (outputParameters.device == paNoDevice)
    handleError("No default output device.");
  outputParameters.channelCount = PortAudio::CHANNEL_COUNT;
  outputParameters.sampleFormat = PortAudio::SAMPLE_TYPE;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  PaStreamCallback* playCallback = &PortAudio::playCallback;

  handleError(Pa_OpenStream(&stream,
			    NULL,
			    &outputParameters,
			    PortAudio::SAMPLE_RATE,
			    PortAudio::FRAMES_PER_BUFFER,
			    paClipOff,
			    playCallback,
			    &data));
  if (stream)
    {
      handleError(Pa_StartStream(stream));
      PaError error;
      while ((error = Pa_IsStreamActive(stream)) == 1)
	  Pa_Sleep(100);
      if (error < 0)
      handleError(error);
      handleError(Pa_CloseStream(stream));
    }
}

PortAudio::~PortAudio()
{
  Pa_Terminate();
}
