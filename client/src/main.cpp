//
// main.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:49:31 2011 by ramnes
// Last update Tue Nov 22 23:13:50 2011 ramnes
//

#include	"BabelClient.hpp"
#include	<cstdlib>
#include	<iostream>

# define	MASTER	"192.168.0.1"
# define	PORT	1337

int		main()
{
  BabelClient* client = new BabelClient();
  if (!client->run())
    return (EXIT_FAILURE);
  if (!client->connectTo(MASTER, PORT))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
