
#include	"Factory.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}

BabelProtocol & Factory::createProtocolClass(int id_class, void * data, size_t size)
{
  BabelProtocol * test = new BabelProtocol();
  (void) id_class;
  (void) data;
  (void) size;

  return *test;
}

