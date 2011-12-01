#include		"BabelProtocol.hpp"

BabelProtocol::BabelProtocol(int cmd, void *data, size_t size)
  : _cmd(cmd),
    _data(data),
    _size(size)
{

}

BabelProtocol::~BabelProtocol()
{

}
