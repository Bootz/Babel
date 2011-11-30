//
// Exception.hh for  in /home/lesueu_l//Desktop/prog/in_prog/Babel/Socket
// 
// Made by louis lesueur
// Login   <lesueu_l@epitech.net>
// 
// Started on  Sun Nov 13 12:37:31 2011 louis lesueur
// Last update Sun Nov 13 12:39:09 2011 louis lesueur
//

#ifndef			__BABEL_EXCEPTION_HH__
# define		__BABEL_EXCEPTION_HH__

# include		<stdexcept>

class BabelException : public std::exception
{
private:
	std::string _msg;

public:
	~BabelException() throw() {}
	BabelException(std::string const & errcode)
		:_msg(buildMsg(errcode)) {}
	const char* what() const throw()
	{
	  return(this->_msg.c_str());
	}

private:
	std::string buildMsg(std::string const & errcode)
	{
	  return errcode;
	}
};

#endif			/*__BABEL_EXCEPTION_HH__*/
