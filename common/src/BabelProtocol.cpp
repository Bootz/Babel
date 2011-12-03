
#include		<stdio.h>
#include		<cstring>
#include		"BabelProtocol.hpp"

//
// main.cpp for Babel in /tmp
// 
// Made by koeth_y
// Login   <koeth_y@epitech.net>
// 
// Started on  Sat Dec  3 21:42:09 2011 koeth_y
// Last update Sat Dec  3 22:29:15 2011 koeth_y
//


Protocol getRegisterProtocol(const std::string& login, const std::string& password)
{
  Protocol protocol;

  RegisterParam param;
  std::strncpy(param.login, login.c_str(), LEN_NAME);
  std::strncpy(param.password, password.c_str(), LEN_NAME);

  protocol.cmd = CL_REGISTER;
  protocol.size = sizeof(param);
  protocol.data = operator new(protocol.size);
  std::memcpy(protocol.data, &param, protocol.size);

  return protocol;
}

Protocol getInfoProtocol(const std::vector<std::string>& contactList)
{
  Protocol protocol;

  InfoParam param;

  param.clientCount = contactList.size();

  protocol.cmd = CL_INFO;
  protocol.size = sizeof(param) + param.clientCount * LEN_NAME;
  protocol.data = operator new(protocol.size);
  std::memcpy(protocol.data, &param, protocol.size);

  // Copy contacts
  int i = 0;
  for (std::vector<std::string>::const_iterator it = contactList.begin(); it != contactList.end(); ++it)
    {
      // Create static equivalent
      char contact[LEN_NAME];
      std::strncpy(contact, it->c_str(), LEN_NAME);
      size_t loginsOffset = sizeof(param) - sizeof(param.logins);
      void* currentLogin = static_cast<char*>(protocol.data) + loginsOffset + LEN_NAME * i;
      // Copy at end
      std::memcpy(currentLogin, contact, LEN_NAME);
      ++i;
    }

  return protocol;
}

