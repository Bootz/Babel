
#include	"Factory.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}

ProtocoleClass & Factory::createProtocolClass(std::string classname)
{
  ProtocoleClass * test = new ProtocoleClass(classname);

  return *test;
}

