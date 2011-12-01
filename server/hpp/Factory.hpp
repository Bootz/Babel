
#include		<string>
#include		"BabelProtocol.hpp"
#include		"BabelEnum.hpp"

class			Factory
{
 public:
  Factory();
  ~Factory();

 public:
  BabelProtocol & createProtocolClass(int enum_class, void * data, size_t size);
};
