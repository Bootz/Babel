//
// BabelProtocol.hpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 21:38:06 2011 by ramnes
// Last update Thu Nov 24 08:16:01 2011 ramnes
//

#ifndef			__BABEL_BABELPROTOCOL_HPP__
# define		__BABEL_BABELPROTOCOL_HPP__


# include		<vector>
# include		<iostream>

static const int LEN_NAME = 30;
static const int LEN_PSWD = 30;

struct RegisterParam
{
  char login[LEN_NAME];
  char password[LEN_PSWD];
};

struct InfoParam
{
  unsigned int clientCount;
  void* logins;
};

enum 	ProtocolCommand
  {
    // Client->Server commands
    CL_REGISTER = 0,
    CL_LOGIN ,
    CL_INFO ,
    CL_QUIT ,

    // Client->Client commands
    CC_CALL ,
    CC_ACCEPT ,
    CC_REFUSE ,
    CC_WAIT ,
    CC_END ,

    // Server->Client commands
    CI_INCOMING ,
    CI_PENDING ,
    CI_ENDED ,
    CI_ACCEPTED ,
    CI_REFUSED ,
    SV_END
  };

const std::string server_cmd_str[]=
  {
    // Client->Server commands
    "CL_REGISTER",
    "CL_LOGIN" ,
    "CL_INFO" ,
    "CL_QUIT" ,

    // Client->Client commands
    "CC_CALL" ,
    "CC_ACCEPT" ,
    "CC_REFUSE" ,
    "CC_WAIT" ,
    "CC_END" ,

    // Client->Server commands
    "CI_INCOMING",
    "CI_PENDING",
    "CI_ENDED",
    "CI_ACCEPTED",
    "CI_REFUSED" ,
    "SV_END"
  };

struct Protocol
{
  ProtocolCommand cmd;
  size_t size;
  void* data;
};

void readProtocol(const Protocol& protocol);
Protocol getRegisterProtocol(const std::string& login, const std::string& password);

#endif			// __BABEL_BABELPROTOCOL_HPP__
