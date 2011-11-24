//
// BabelClient.cpp for Babel project
// 
// Made by ramnes
// <perso@ramnes.eu>
// 
// Started on  Tue Nov 22 19:23:34 2011 by ramnes
// Last update Thu Nov 24 11:52:02 2011 ramnes
//

#include	<cstdlib>
#include	<algorithm>
#include	<fstream>
#include	<iostream>

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

bool		BabelClient::connectTo()
{
  std::map<std::string, std::string>::iterator it;
  std::map<std::string, std::string>::iterator it2;

  if ((it = this->_cfg.find("hostname")) != this->_cfg.end()
       && (it2 = this->_cfg.find("port")) != this->_cfg.end())
    return (this->connectTo(it->second, atoi(it2->second.c_str())));
  return (this->connectTo(DEF_MASTER, DEF_PORT));
}

// loadCfg : récupère des infos dans le fichier passé en paramètre
// retourne true si des attributs de BabelClient ont été modifiés 

static void	del(std::string& s, char c)
{
  size_t	pos = 0;

  if (!s.empty())
    while ((pos = s.find(c)) != s.npos)
      s.erase(pos, 1);
}

bool     	BabelClient::loadCfg(const std::string& filename)
{
  size_t	pos = 0;
  std::string	line;
  std::ifstream ifs(filename.c_str());

  if (!ifs)
    {
      std::cout << "warning: Impossible de lire " << filename << std::endl;
      return (false);
    }
  while (std::getline(ifs, line))
    {
      del(line, ' ');
      del(line, '\t');
      if (line.substr(0, 2) != "//"
	  && (pos = line.find("=")) != line.npos)
	{
	  std::string	id;
	  std::string	val;

	  id = line.substr(0, pos);
	  val = line.substr(pos + 1, line.size());
	  this->_cfg.insert(std::pair<std::string, std::string>(id, val));
	}
    }
  return (true);
}
