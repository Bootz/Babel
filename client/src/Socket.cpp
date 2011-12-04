//
// Socket.cpp for Babel in /home/xsyann/scm/Babel/client/unit-test/socket
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sun Dec  4 18:59:13 2011 koeth_y
// Last update Sun Dec  4 22:05:24 2011 koeth_y
//

#include <iostream>
#include <QtNetwork>
#include <QTcpSocket>
#include "Socket.hpp"

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
# define msleep(X) Sleep(X)
#else // UNIX
# define msleep(X) usleep((X) * 1000)
#endif

Socket::Socket()
  : _client(NULL)
{
}

int Socket::_waitClient()
{
  int bytesAvailable = -1;

  while (_client->state() == QAbstractSocket::ConnectedState && bytesAvailable < 0)
    {
      if (_client->waitForReadyRead(Socket::DELTA))
	bytesAvailable = _client->bytesAvailable();
      else
	msleep(Socket::DELTA);
    }
  return bytesAvailable;
}

void* Socket::receive()
{
  void* data = NULL;
  int bytesAvailable = this->_waitClient();
  if (bytesAvailable > 0)
    {
      QDataStream in(_client);
      in.setVersion(QDataStream::Qt_4_0);
      if (bytesAvailable < static_cast<int>(sizeof(quint16)))
	return data;
      quint16 blockSize = 0;
      in >> blockSize;
      std::cout << blockSize << std::endl;
      if (_client->bytesAvailable() < blockSize)
	return data;

      char* buffer;
      in >> buffer;
      data = buffer;
    }
  return data;
}

bool Socket::send(const void* data, size_t size)
{
  if (data && size > 0)
    {
      QByteArray block;
      QDataStream out(&block, QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_4_0);
      out << static_cast<quint16>(0);
      out.writeBytes(static_cast<const char*>(data), size);
      out.device()->seek(0);
      out << static_cast<quint16>(block.size() - sizeof(quint16));
      _client->write(block);
      if (!_client->waitForBytesWritten())
	throw ISocket::Exception("Client closed");
    }
  return true;
}

bool Socket::isConnected() const
{
  return this->_client->state() == QAbstractSocket::ConnectedState;
}

bool Socket::run(const std::string& ip, short port)
{
  QHostAddress host(ip.c_str());

  this->_client = new QTcpSocket();
  this->_client->connectToHost(host, port);
  if (!this->_client->waitForConnected(3000))
    throw ISocket::Exception("Can't etablish connection");
  
  return true;
}

Socket::~Socket()
{
  if (this->_client)
    delete this->_client;
}

