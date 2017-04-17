//
// Created by brout_m on 15/04/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <thread>
#include <condition_variable>
#include <vector>
#include "SafeQ.hpp"
#include "Enums.hpp"

namespace threadpool
{
    template <typename OrderT, typename ResultT>
    class ThreadPool
    {
    public:
        typedef struct data
        {
            std::atomic<bool>          s_over;
            threadpool::SafeQ<OrderT>  s_orderQ;
            threadpool::SafeQ<ResultT> s_resultQ;

            data()
            {
                s_over.store(false);
            };

        }   Data;

    public:
        ThreadPool(size_t p_maxThreads = 1)  :
                m_maxThread(p_maxThreads),
                m_threads(),
                m_runCalled(false)
        {

        }

        ~ThreadPool()
        {
            if (m_runCalled)
            {
                for (size_t i = 0; i < m_maxThread; ++i)
                {
                    m_threads[i].join();
                }
            }
        }


        bool isNotFull(size_t maxQuantity) const
        {
            return (m_data.s_orderQ.size() < maxQuantity);
        }

        ///
        /// \fn void pushAction(OrderT &&p_action)
        /// \brief Push an order to the queue and signal waiting threads
        /// \param p_action order to push
        ///
        void pushAction(OrderT &&p_action)
        {
            m_data.s_orderQ.push(std::move(p_action));
            m_data.s_orderQ.signal();
        }

        ///
        /// \fn void run(std::function<void(threadpool::ThreadPool<OrderT, ResultT>::data &)> fn)
        /// \brief Launch the threads with a function provide by the user as a parameter.
        ///     The function must use the safeQ provided in the data structure to pop orders,
        ///     process them and push results.
        /// \param fn function, lambda or functor to execute in each thread, it MUST accepts a
        ///     threadpool::ThreadPool<OrderT, ResultT>::data reference as a parameter
        ///
        void run(std::function<void(threadpool::ThreadPool<OrderT, ResultT>::data &)> fn)
        {
            if (!m_runCalled)
            {
                for (size_t i = 0; i < m_maxThread; ++i)
                {
                    m_threads.push_back(std::thread(fn, std::ref(m_data)));
                }
                m_runCalled = true;
            }
        }

        ///
        /// \fn void setOver(bool p_over)
        /// \brief call this function to unlock all threads waiting on queues and
        ///     stopping the pool
        /// \param p_over
        ///
        void setOver(bool p_over)
        {
            m_data.s_over = p_over;
            m_data.s_resultQ.signal_all();
            m_data.s_orderQ.signal_all();
            join_all();
        }

        ///
        /// \fn threadpool::SafeQ<ResultT> &getResults()
        /// \brief return the result safeQ to allow its manipulation to users
        /// \return the result safeQ
        threadpool::SafeQ<ResultT> &getResults()
        {
            return (m_data.s_resultQ);
        }

    private:
        size_t                          m_maxThread;
        std::vector<std::thread>        m_threads;
        bool                            m_runCalled;
        Data                            m_data;

        // Joins all the threads, invisible to the user
        void join_all()
        {
            if (m_runCalled)
            {
                for (size_t i = 0; i < m_maxThread; ++i)
                {
                    m_threads[i].join();
                }
                m_runCalled = false;
            }
        }
    };
}

#endif //CPP_PLAZZA_THREADPOOL_HPP
