//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_COREGUI_HPP
#define CPP_PLAZZA_COREGUI_HPP

#include <string>
#include <memory>
#include "ICore.hpp"
#include "GUI.hpp"

namespace plazza
{
    class CoreGui : public ICore
    {
    public:
        CoreGui();
        ~CoreGui();
        void initialize(int ac, char **av, char **env);
        int run();

    private:
        std::unique_ptr<QApplication>       m_app;
        std::unique_ptr<gui::GUI>           m_gui;

        void check_env(char **env);
    };
}

#endif //CPP_PLAZZA_CORE_HPP
