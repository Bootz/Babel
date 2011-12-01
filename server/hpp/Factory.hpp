
#include		<string>
#include		"ProtocoleClass.hpp"
 
class			Factory
{
 public:
  Factory();
  ~Factory();

 public:
  ProtocoleClass & createProtocolClass(std::string classname);
};
