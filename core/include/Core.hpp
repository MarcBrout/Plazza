//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_CORE_HPP
#define CPP_PLAZZA_CORE_HPP

#include "ICore.hpp"
#include "NoGUI.hpp"

namespace plazza
{
    class Core : public ICore
    {
    public:
        Core();
        ~Core(){};
        void initialize(int ac, char **av, char **env);
        int run();

    private:
        std::unique_ptr<NoGUI>  m_noGui;
        size_t                  m_max_threads;
    };
}

#endif //CPP_PLAZZA_CORE_HPP
