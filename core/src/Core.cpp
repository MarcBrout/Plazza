//
// Created by brout_m on 18/04/17.
//

#include "Core.hpp"

void plazza::Core::initialize(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
}

int plazza::Core::run()
{
    m_noGui = std::make_unique<NoGUI>();
    if (m_noGui == nullptr)
        throw (std::bad_alloc());
    return (m_noGui->run(m_max_threads));
}

plazza::Core::Core() :
    m_max_threads(5)
{

}
