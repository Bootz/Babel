//
// main.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:49:31 2011 by ramnes
// Last update Tue Nov 22 20:13:40 2011 ramnes
//

#include	"BabelClient.hpp"
#include	<iostream>

int		main()
{
  BabelClient* client = new BabelClient();
  return (client->run());
}
