//
// main.cpp for Babel in /Users/yannkoeth/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 17:06:21 2011 koeth_y
// Last update Sun Dec  4 22:55:48 2011 koeth_y
//

#include "UThread.hpp"
#include "Socket.hpp"
#include "SocketServer.hpp"
#include "PortAudio.hpp"
#include "AudioData.hpp"

#include <iostream>

typedef UThread Thread;

struct ServerData
{
  bool isServer;
  IThread* serverThread;
};

struct ClientData
{
  bool isServer;
  std::string login;
  IThread* clientThread;
};

#define RECORD_TIME 800

static void serverHandleCallback(void* data)
{
  if (data)
    {
      AudioData audioData(PortAudio::SAMPLE_RATE, PortAudio::CHANNEL_COUNT, RECORD_TIME);
      audioData.setData(static_cast<AudioData::Sample*>(data));
      IAudioIO* audioIO = new PortAudio;
      audioIO->startPlay(audioData);
    }
}

static void* serverCallback(void* arg)
{
  try
    {
      ServerData* data = static_cast<ServerData*>(arg);
      SocketServer* server = new SocketServer;
      std::string host = "127.0.0.1";
      if (!data->isServer)
	  host = "127.0.0.2";

      server->run(serverHandleCallback, host);
      delete server;
      data->serverThread->exit();
    }
  catch (ISocket::Exception& e)
    {
      std::cerr << e.what() << std::endl; 
    }

  return NULL;
}

static void* clientCallback(void* arg)
{
  ClientData* data = static_cast<ClientData*>(arg);
  std::string host = "127.0.0.2";
  if (!data->isServer)
      host = "127.0.0.1";

  try
    {
      ISocket* client = new Socket();

      if (client->run(host))
	{
	  IAudioIO* audioIO = new PortAudio;

	  while (client->isConnected())
	    {
	      //	      std::string tosend = "recorded.. from " + data->login;
	      audioIO->startRecord(RECORD_TIME);
	      AudioData* data = audioIO->getRecorded();

	      client->send(data->getData(), data->getSize());
	      //	      sleep(1);
	    }
	  delete audioIO;
	}
      delete client;
      data->clientThread->exit();
    }    
  catch (ISocket::Exception& e)
    {
      std::cerr << e.what() << std::endl; 
    }
  catch (IAudioIO::Exception& e)
    {
      std::cerr << e.what() << std::endl; 
    }
  return NULL;
}

int main(int argc, char* argv[])
{
  try
    {
      IThread* serverThread = new Thread;
      IThread* clientThread = new Thread;

      ServerData sdata;
      sdata.isServer = (argc >= 2);
      sdata.serverThread = serverThread;
      serverThread->run(serverCallback, &sdata);

      ClientData cdata;
      cdata.isServer = (argc >= 2);
      cdata.login = "Unknown";
      if (argc >= 2)
	cdata.login = argv[1];
      cdata.clientThread = clientThread;
      if (sdata.isServer)
	sleep(2);
      clientThread->run(clientCallback, &cdata);

      clientThread->wait();
      delete clientThread;
      delete serverThread;
    }
  catch (IThread::Exception& e)
    {
      std::cerr << "Babel error: " << e.what() << std::endl; 
    }
  std::cout << "Bye" << std::endl;
  return 0;
}
