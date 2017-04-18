//
// Created by brout_m on 18/04/17.
//

#include "CoreGui.hpp"

plazza::CoreGui::~CoreGui()
{

}

plazza::CoreGui::CoreGui()
{

}

void plazza::CoreGui::initialize(int ac, char **av, char **env)
{
    check_env(env);

    m_app = std::make_unique<QApplication>(ac, av);
    if (m_app == nullptr)
        throw (std::bad_alloc());

    m_gui = std::make_unique<gui::GUI>();
    if (m_gui == nullptr)
        throw (std::bad_alloc());
}

int plazza::CoreGui::run()
{
    m_gui->show();
    return (m_app->exec());
}

void plazza::CoreGui::check_env(char **env)
{
    char **l_cpy = env;

    if (env == nullptr)
        throw (std::invalid_argument("Environment is null"));

    while (*l_cpy != nullptr)
    {
        std::string l_str(*l_cpy);

        if (!l_str.compare(0, l_str.find_first_of('='), "DISPLAY"))
            return ;
        ++l_cpy;
    }
    throw (std::invalid_argument("Missing DISPLAY environment variable"));
}
