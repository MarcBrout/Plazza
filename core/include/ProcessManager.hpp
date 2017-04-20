//
// Created by brout_m on 20/04/17.
//

#ifndef CPP_PLAZZA_PROCESSMANAGER_HPP
#define CPP_PLAZZA_PROCESSMANAGER_HPP

#include <vector>
#include "ICommunication.hpp"
#include "Forker.hpp"

namespace plazza
{
    class ProcessManager
    {
    public:
        ProcessManager(ICommunication *p_com);
        ~ProcessManager() {};

    private:
        ICommunication              *m_com;
        fork::Forker<int, size_t>   m_forker;

        // Deleted Methods
        ProcessManager(ProcessManager const&) = delete;
        ProcessManager(ProcessManager &&) = delete;
        ProcessManager &operator=(ProcessManager const&) = delete;
        ProcessManager &operator=(ProcessManager &&) = delete;
    };
}

#endif //CPP_PLAZZA_PROCESSMANAGER_HPP
