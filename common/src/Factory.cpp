
#include	"Factory.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}

BabelProtocol & Factory::createProtocolClass(int enum_class, void * data, size_t size)
{    
  std::string cmd = server_cmd_str[enum_class];
  
  BabelProtocol * test = new BabelProtocol();
  
  return *test;
}

