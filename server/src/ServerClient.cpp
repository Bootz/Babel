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
  : _connected(false),
    _name(name),
    _socket(sock)
{
}

ServerClient &	ServerClient::operator=(ServerClient const &c)
{
  this->_name = c.getName();
  this->_password = c.getPassword();
  this->_connected = c.isConnected();
  this->_ip = c.getIp();
  return *this;
}

ServerClient::ServerClient(const std::string & name,
			   const std::string & password,
			   const std::string &ip)
  : _password(password),
    _connected(true),
    _name(name),
    _ip(ip)
{
}

ServerClient::~ServerClient()
{
}

std::string	ServerClient::getName() const
{
  return this->_name;
}

void		ServerClient::destruct()
{
  this->_name = '\0';
  this->_password = '\0';
  this->_ip = '\0';
  this->_connected = false;
}

void		ServerClient::setConnected(bool value)
{
  this->_connected = value;
}

std::string	ServerClient::getIp() const
{
  return this->_ip;
}

std::string	ServerClient::getPassword() const
{
  return this->_password;
}

bool		ServerClient::isConnected() const
{
  return this->_connected;
}

void		ServerClient::addContact(int contact)
{
  this->_contacts.push_back(contact);
}

std::list<int>	ServerClient::getContacts() const
{
  return this->_contacts;
}
