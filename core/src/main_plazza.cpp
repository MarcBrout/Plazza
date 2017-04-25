//
// Created by brout_m on 18/04/17.
//

#include <exception>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <signal.h>
#include "Core.hpp"
#include "Logger.hpp"

void my_handler(int toto)
{
    signal(SIGPIPE, &my_handler);
    (void)toto;
    std::cout << "GOT SIGPIPE" << std::endl;
}

int main(int ac, char **av, char **env)
{
    struct stat st;

    if (ac != 2)
    {
        std::cerr << av[0] << ": [NB_THREADS]" << std::endl;
        return (EXIT_FAILURE);
    }

    signal(SIGPIPE, &my_handler);

    if (stat("./files", &st) == -1) {
        mkdir("./files", 0700);
    }
  plazza::Logger::getInstance().disableStdout();
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
