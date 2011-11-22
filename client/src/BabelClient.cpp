//
// BabelClient.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:23:34 2011 by ramnes
// Last update Tue Nov 22 23:13:02 2011 ramnes
//

#include	"BabelClient.hpp"
#include	<iostream>

BabelClient::BabelClient()
{
  std::cout << "Salutations, noble péon !" << std::endl;
}

BabelClient::~BabelClient()
{
  std::cout << "Bye !" << std::endl;
}

bool		BabelClient::run() const
{
  std::cout << "Je suis un ouf et je rox le babel en oneshot" << std::endl;
  // TODO: lancer le GUI
  return (true);
}

bool		BabelClient::connectTo(const std::string& hostname,
				       const int port) const
{
  std::cout << "Connecting to " << hostname << ":" << port << " ..." << std::endl;
  return (true);
}
