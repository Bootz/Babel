
#include		"BabelProtocol.hpp"

int		BabelProtocol::getCmd(void) const
{
  return this->_cmd;
}

size_t		BabelProtocol::getSize(void) const
{
  return this->_size;
}

char*		BabelProtocol::getData(void) const
{
    return this->_data;
}

std::string	BabelProtocol::getChecksum(void) const
{
  return this->_checksum;
}

void		BabelProtocol::setCmd(int cmd)
{
  this->_cmd = cmd;
}

void		BabelProtocol::setSize(size_t size)
{
  this->_size = size;
}

void		BabelProtocol::setData(char *data)
{
  this->_data = data;
}

void		BabelProtocol::setChecksum(char *checksum)
{
  this->_checksum = checksum;
}

void		BabelProtocol::setRequest(int cmd, void *data, size_t size)
{
  (void) cmd;
  (void) data;
  (void) size;
}
