/***********************************************************************
 * Module:  clientManager.cpp
 * Author:  Emax
 * Modified: jeudi 17 novembre 2011 12:02:58
 * Purpose: Implementation of the class clientManager
 ***********************************************************************/

#include "clientManager.hpp"

clientManager::clientManager(ISocket & sock)
  : _sock(sock)
{
}

clientManager::~clientManager()
{
}

bool		clientManager::add(std::string name, std::string password, std::string ip, int socket)
{
  ServerClient		buffer(name, password, ip, this->_clients.size(), socket);

  this->_clients.push_back(buffer);
  return (true);
}

int		clientManager::getSocket(int id)
{
  return (this->_clients[id].getSocket());
}

std::string	 clientManager::getName(int id)
{
  return (this->_clients[id].getPseudo());
}

bool clientManager::deco(int id)
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

  toSend.append(tmp.getPseudo());
  for (std::list<int>::iterator it= tmp.getContacts().begin();
       it != tmp.getContacts().end();
       ++it)
    {
      // envoi de toSend a l'ID [*it].
    }
  return true;
}

bool			clientManager::isInList(unsigned short i) // c' est quoi i ?
{
  if (i > this->_clients.size()) // || this->_clients[i]) -> vraiment necessaire?
    return (false);
  return (true);
}

// serverClient &		clientManager::find(std::string & name)
// {
//   int			i = 0;

//   while (i < this->_clients.size())
//     {
//       if (this->_clients[i].getPseudo().compare(name) == 0)
// 	return (this->_clients[i]);
//      ++i;
//     }
//   return NULL;
// }

//A quelle moment on peut avoir besoin de cette fonction? je ne vois pas son interet
