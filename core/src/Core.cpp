//
// Created by brout_m on 18/04/17.
//

#include "Core.hpp"

void plazza::Core::initialize(int ac, char **av, char **env)
{
    int l_args;
    std::string l_av1 { av[1] };

    (void)ac;
    (void)env;

    if ((l_args = std::stoi(l_av1)) <= 0)
        throw std::invalid_argument("Threads count must be positive");
    m_max_threads = static_cast<size_t >(l_args);
}

int plazza::Core::run()
{
    m_noGui = std::make_unique<NoGUI>();
    if (m_noGui == nullptr)
        throw (std::bad_alloc());
    return (m_noGui->run(m_max_threads));
}

plazza::Core::Core() :
    m_max_threads(0)
{
}
