#ifndef		__BABEL_BABELENUM_HPP__
# define	__BABEL_BABELENUM_HPP__

typedef enum
  {
    // Client->Server commands
    CL_REGISTER = 0,
    CL_LOGIN ,
    CL_INFO ,
    CL_QUIT ,

    // Client->Client commands
    CC_CALL ,
    CC_ACCEPT ,
    CC_REFUSE ,
    CC_WAIT ,
    CC_END ,

    // Server->Client commands
    CI_INCOMING ,
    CI_PENDING ,
    CI_ENDED ,
    CI_ACCEPTED ,
    CI_REFUSED ,
    SV_END
  }	ENUM_CMD;

  const std::string server_cmd_str[]=
    {
      // Client->Server commands
      "CL_REGISTER",
      "CL_LOGIN" ,
      "CL_INFO" ,
      "CL_QUIT" ,

      // Client->Client commands
      "CC_CALL" ,
      "CC_ACCEPT" ,
      "CC_REFUSE" ,
      "CC_WAIT" ,
      "CC_END" ,

      // Client->Server commands
      "CI_INCOMING",
      "CI_PENDING",
      "CI_ENDED",
      "CI_ACCEPTED",
      "CI_REFUSED" ,
      "SV_END"
    };

#endif		// __BABEL_BABELENUM_HPP__
