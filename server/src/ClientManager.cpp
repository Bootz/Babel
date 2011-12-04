/***********************************************************************
 * Module:  clientManager.cpp
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Implementation of the class clientManager
 ***********************************************************************/

#include "ClientManager.hpp"

ClientManager::ClientManager(ISocket & sock)
  : _sock(sock)
{
}

ClientManager::~ClientManager()
{
}

void		ClientManager::createClient(SOCKET sock)
{
  ServerClient	cli(sock, "Default");

  for (int i = 0; sock > int(this->_clients.size()); ++i)
    {
      this->_clients.push_back(cli);
    }
  this->_clients.push_back(cli);
}

void			ClientManager::delClient(int fd)
{
  this->_clients[fd].destruct();
}

bool		ClientManager::add(const std::string & name,
				   const std::string & password,
				   const std::string & ip,
				   __attribute__((unused))int socket)
{
  ServerClient		buffer(name, password, ip);

  this->_clients.push_back(buffer);
  return (true);
}

std::string	 ClientManager::getName(int id) const
{
  return (this->_clients[id].getName());
}

bool ClientManager::deco(int id)
{
 ServerClient		tmp = this->_clients[id];
 Protocol protocol;

 protocol.cmd = CI_DECO;
 protocol.size = 0;
 protocol.data = NULL;

  for (std::list<int>::iterator it= tmp.getContacts().begin();
       it != tmp.getContacts().end();
       ++it)
    {
      this->_sock.send_d(*it, reinterpret_cast<char *> (&protocol));
	// envoi de toSend a l'ID [*it].
    }
  return true;
}

bool			ClientManager::isInList(unsigned short i) const
{
  if (i <= this->_clients.size())
    return (true);
  return (false);
}

bool			ClientManager::isInList(std::string & name) const
{
  for (unsigned int i = 0; i <= this->_clients.size(); ++i)
    if (this->_clients[i].getName() == name)
      return true;
  return false;
}

ServerClient 		ClientManager::getClient(const SOCKET sock) const
{
  return this->_clients[sock];
}

std::vector<ServerClient>	ClientManager::getClients() const
{
  return this->_clients;
}

void			ClientManager::addContact(int fd, int contact)
{
  this->_clients[fd].addContact(contact);
}

std::list<int>		ClientManager::getContacts(int fd) const
{
  return this->_clients[fd].getContacts();
}
