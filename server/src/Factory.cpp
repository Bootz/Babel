
#include	"Factory.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}

BabelProtocol & Factory::createProtocolClass(int id_class, void * data, size_t size)
{
  BabelProtocol * test = new BabelProtocol(id_class, data, size);
  (void) id_class;

  return *test;
}

