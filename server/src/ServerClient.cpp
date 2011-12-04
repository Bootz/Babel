/***********************************************************************
 * Module:  serverClient.cpp
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Implementation of the class serverClient
 ***********************************************************************/

#include "ServerClient.hpp"

////////////////////////////////////////////////////////////////////////
// Name:       ServerClient::~ServerClient()
// Purpose:    Implementation of ServerClient::~ServerClient()
// Return:     int
////////////////////////////////////////////////////////////////////////

ServerClient::ServerClient(SOCKET & sock, std::string name)
  : _password('\0'),
    _connected(false),
    _name(name),
    _ip('\0'),
    _socket(sock)
{
}

ServerClient &	ServerClient::operator=(ServerClient const &c)
{
  this->_socket = c.getSocket();
  this->_name = c.getName();
  this->_password = c.getPassword();
  this->_connected = c.isConnected();
  this->_ip = c.getIp();
  return *this;
}

ServerClient::ServerClient(const std::string & name,
			   const std::string & password,
			   const std::string &ip,
			   int socket)
  : _password(password),
    _connected(true),
    _name(name),
    _ip(ip),
    _socket(socket)
{
}

ServerClient::~ServerClient()
{
}

void		ServerClient::setSocket(int sock)
{
  this->_socket = sock;
}

std::string	ServerClient::getName() const
{
  return this->_name;
}

std::string	ServerClient::getIp() const
{
  return this->_ip;
}

int		ServerClient::getSocket() const
{
  return this->_socket;
}

std::string	ServerClient::getPassword() const
{
  return this->_password;
}

bool		ServerClient::isConnected() const
{
  return this->_connected;
}

std::list<int>	ServerClient::getContacts() const
{
  return this->_contacts;
}
