//
// main.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:49:31 2011 by ramnes
// Last update Sun Dec  4 18:15:14 2011 guillaume gelin
//

#include	"BabelClient.hpp"
#include	<cstdlib>
#include	<iostream>

int		main()
{
  BabelClient* client = new BabelClient();
  client->run();
  client->loadConfig("autoexec.cfg");
  client->connectTo();
  delete client;
  return (EXIT_SUCCESS);
}
