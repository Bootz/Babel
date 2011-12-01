
#include		<string>
#include		"BabelProtocol.hpp"
 
class			Factory
{
 public:
  Factory();
  ~Factory();

 public:
  BabelProtocol & createProtocolClass(int id_class, void * data, size_t size);
};
