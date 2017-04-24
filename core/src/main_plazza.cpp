//
// Created by brout_m on 18/04/17.
//

#include <exception>
#include <cstdlib>
#include <iostream>
#include "Core.hpp"
#include "Logger.hpp"

int main(int ac, char **av, char **env)
{
  plazza::Logger::getInstance().enableStdout();
  plazza::Logger::getInstance().log(plazza::Logger::INFO, "start\n");
    try
    {
        plazza::Core    l_core;
        l_core.initialize(ac, av, env);
        l_core.run();
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
