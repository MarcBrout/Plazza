//
// Created by brout_m on 12/04/17.
//

#include <iostream>
#include <sys/stat.h>
#include "CoreGui.hpp"

int main(int ac, char **av, char **env)
{
  struct stat st;

  if (stat("./files", &st) == -1) {
    mkdir("./files", 0700);
  }
  try
    {
      plazza::CoreGui l_coreGui;
      l_coreGui.initialize(ac, av, env);
      l_coreGui.run();
      return (EXIT_SUCCESS);
    }
  catch (std::exception &err)
    {
      if (err.what())
	std::cerr << err.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (...)
    {
      return (EXIT_FAILURE);
    }
}
