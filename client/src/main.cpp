//
// main.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:49:31 2011 by ramnes
// Last update Thu Nov 24 12:08:28 2011 ramnes
//

#include	"BabelClient.hpp"
#include	<cstdlib>
#include	<iostream>

int		main()
{
  BabelClient* client = new BabelClient();

  if (!client->run())
    return (EXIT_FAILURE);
  client->loadConfig("autoexec.cfg");
  if (!client->connectTo())
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
