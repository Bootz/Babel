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

ServerClient::ServerClient(unsigned int sock)
  : _socket(sock);
{
}

ServerClient::ServerClient(std::string name, std::string password, std::string ip, unsigned short id, int socket)
  : _password(password),
    _connected(true),
    _name(name),
    _ip(ip),
    _id(id),
    _socket(socket)
{
}

// ServerClient& ServerClient::operator=(const ServerClient& other)
//   : _password(other._password),
//     _connected(other._connected),
//     _contacts(other._contacts)
//     _name(other._name),
//     _ip(other._ip),
//     _id(other._id),
//     _socket(other._socket)
// {
// }

ServerClient::~ServerClient()
{
}

std::string	ServerClient::getName() const
{
  return this->_name;
}

unsigned short	ServerClient::getId() const
{
  return this->_id;
}

std::string	ServerClient::getIp() const
{
  return this->_ip;
}

int		ServerClient::getSocket() const
{
  return this->_socket;
}

bool		ServerClient::isConnected() const
{
  return this->_connected;
}

std::list<int>	ServerClient::getContacts() const
{
  return this->_contacts;
}
