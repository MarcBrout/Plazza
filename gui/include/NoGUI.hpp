//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_NOGUI_HPP
#define CPP_PLAZZA_NOGUI_HPP

#include "ThreadPool.hpp"

namespace plazza
{
    class NoGUI
    {
    public:
        NoGUI();
        int run(size_t p_thread_max);

    private:
        threadpool::ThreadPool<bool, std::string>  m_threadpool;
    };
}

#endif //CPP_PLAZZA_NOGUI_HPP
