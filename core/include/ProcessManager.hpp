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

        void process(std::vector<std::string, std::string> &orders,
                     std::vector<std::string> &results,
                     size_t p_max_threads);

    private:
        ICommunication              *m_com;
        plazza::Forker<int, size_t>   m_forker;

        int load_balancer(std::vector<std::pair<int, size_t >> const& p_sockets,
                          size_t p_max_threads);

        // Deleted Methods
        ProcessManager(ProcessManager const&) = delete;
        ProcessManager(ProcessManager &&) = delete;
        ProcessManager &operator=(ProcessManager const&) = delete;
        ProcessManager &operator=(ProcessManager &&) = delete;
    };
}

#endif //CPP_PLAZZA_PROCESSMANAGER_HPP
