//
// Created by brout_m on 18/04/17.
//

#include <exception>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include "Core.hpp"

int main(int ac, char **av, char **env)
{
    struct stat st = {0};

    if (stat("./files", &st) == -1) {
        mkdir("./files", 0700);
    }
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