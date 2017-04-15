//
// Created by brout_m on 15/04/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <thread>
#include <condition_variable>
#include <vector>
#include "SafeQ.hpp"

namespace threadpool
{
    template <typename OrderT, typename ReturnT>
    class ThreadPool
    {
    public:
        typedef struct data
        {
            std::atomic<bool>               s_over;
            threadpool::SafeQ<OrderT>       s_safeQ;
            threadpool::SafeQ<ReturnT>      s_resultQ;
            std::condition_variable         s_cond;
            std::mutex                      s_condMutex;

            data() :
                    s_over(false)
            {};

        }   Data;

    public:
        ThreadPool(size_t p_maxThreads = 1)  :
                m_maxThread(p_maxThreads),
                m_threads(p_maxThreads, std::thread()),
                m_data()
        {

        }

        ~ThreadPool()
        {
            for (std::thread &r_thread : m_threads)
            {
                r_thread.join();
            }
        }

        bool isNotFull() const
        {
            return (m_data.s_safeQ.size() < m_maxThread * 2);
        }

        void pushAction(OrderT p_action)
        {
            m_data.s_safeQ.push(p_action);
            m_data.s_safeQ.signal();
        };

        void run(void (*fn)(threadpool::ThreadPool::Data &))
        {
            for (std::thread &r_thread : m_threads)
            {
                r_thread = std::thread(fn, m_data);
            }
        };

        void setOver(bool p_over)
        {
            m_data.s_over = p_over;
        }

    private:
        size_t                          m_maxThread;
        std::vector<std::thread>        m_threads;
        Data                            m_data;
    };
}

#endif //CPP_PLAZZA_THREADPOOL_HPP
