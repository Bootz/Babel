/***********************************************************************
 * Module:  main.cpp
 * Author:  Emax
 * Modified: jeudi 24 novembre 17:52
 * Purpose: Launch the whole program
 ***********************************************************************/

#include	<cstdlib>
#include	"Server.hpp"

void		launch_program()
{
  Server& ptr1 = Server::getInstance();

  ptr1.main_loop();
}

int		 main( __attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av)
{
  if (ac != 1)
    return (EXIT_FAILURE);
  launch_program();
  return (EXIT_SUCCESS);
}
