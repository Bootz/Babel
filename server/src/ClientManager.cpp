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
      cli.setSocket(i);
      this->_clients.push_back(cli);
    }
  cli.setSocket(sock);
  this->_clients.push_back(cli);
}

bool		ClientManager::add(const std::string & name,
				   const std::string & password,
				   const std::string & ip,
				   int socket)
{
  ServerClient		buffer(name, password, ip, socket);

  this->_clients.push_back(buffer);
  return (true);
}

int		ClientManager::getSocket(int id) const
{
  return (this->_clients[id].getSocket());
}

std::string	 ClientManager::getName(int id) const
{
  return (this->_clients[id].getName());
}

bool ClientManager::deco(int id)
{
  // TROP LOURD
  // while (!tmp.getContacts().empty())
  //   {
  //     toSend.assign("DECO ");
  //     toSend.append(this->_clients[tmp.getContacts().front()].getPseudo());
  //     if (this->_sock(this->_clients[tmp.getContacts()].getSocket(), toSend) <= 5)
  // 	return (false);
  //     tmp.getContacts().pop_front();
  //   }
  // return (true);

 ServerClient		tmp = this->_clients[id]; // tmp = le client traite
  std::string		toSend = "DECO ";

  toSend.append(tmp.getName());
  for (std::list<int>::iterator it= tmp.getContacts().begin();
       it != tmp.getContacts().end();
       ++it)
    {
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

  // ServerClient &		getClient(std::string & name) const
  // {

  // }
