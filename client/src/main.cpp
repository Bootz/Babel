//
// main.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:49:31 2011 by ramnes
// Last update Thu Dec  1 18:04:25 2011 ramnes
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
