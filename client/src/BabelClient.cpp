//
// BabelClient.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:23:34 2011 by ramnes
// Last update Thu Nov 24 12:33:08 2011 ramnes
//

#include	<algorithm>
#include	<fstream>
#include	<iostream>
#include	<sstream>

#include	"BabelClient.hpp"

BabelClient::BabelClient()
{
  std::cout << "Salutations, noble péon !" << std::endl;
}

BabelClient::~BabelClient()
{
  std::cout << "Bye !" << std::endl;
}

bool     	BabelClient::run()
{
  std::cout << "Je suis un ouf et je rox le babel en oneshot" << std::endl;
  // TODO: lancer le GUI
  return (true);
}

bool     	BabelClient::connectTo(const std::string& hostname,
				       const int port) const
{
  std::cout << "Connecting to " << hostname << ":" << port << " ..." << std::endl;
  return (true);
}

static int	atoi(const std::string& s)
{
  int	res;
  std::stringstream ss(s, std::stringstream::in);

  if (ss >> res)
    return (res);
  return (0);
}

bool		BabelClient::connectTo()
{
  std::map<std::string, std::string>::const_iterator it;
  std::map<std::string, std::string>::const_iterator it2;

  if ((it = this->_config.find("hostname")) != this->_config.end()
       && (it2 = this->_config.find("port")) != this->_config.end())
    return (this->connectTo(it->second, atoi(it2->second)));
  return (this->connectTo(DEFAULT_MASTER, DEFAULT_PORT));
}

// loadConfig : récupère des infos dans le fichier passé en paramètre
// retourne true si des attributs de BabelClient ont été modifiés 

bool     	BabelClient::loadConfig(const std::string& filename)
{
  size_t	pos = 0;
  std::string	line;
  std::ifstream ifs(filename.c_str());

  if (!ifs)
    {
      std::cout << "warning: can't read " << filename << std::endl;
      return (false);
    }
  while (std::getline(ifs, line))
    {
      line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
      line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
      if (line.substr(0, 2) != "//"
	  && (pos = line.find("=")) != line.npos)
	{
	  std::string	id;
	  std::string	val;

	  id = line.substr(0, pos);
	  val = line.substr(pos + 1, line.size());
	  this->_config.insert(std::pair<std::string, std::string>(id, val));
	}
    }
  return (true);
}
