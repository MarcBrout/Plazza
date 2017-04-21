//
// Created by brout_m on 15/04/17.
//

#ifndef CPP_PLAZZA_SAFEQ_HPP
#define CPP_PLAZZA_SAFEQ_HPP

#include <deque>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace threadpool
{
    template<typename T>
        class SafeQ
    {
    public:
        SafeQ() :
                m_finished(false)
        {
        }

        ~SafeQ() {};

        void push(T &&p_value)
        {
            std::lock_guard<std::mutex> l_lock(m_mutex);

            m_q.push_front(std::move(p_value));
        }

        bool tryPop(T *p_value)
        {
            std::lock_guard<std::mutex> l_lock(m_mutex);

            if (!m_q.size())
                return (false);

            *p_value = m_q.back();
            m_q.pop_back();
            return (true);
        }

        bool isFinished(void)
        {
            return (m_finished);
        }

        void setFinished(void)
        {
            m_finished = true;
        }

        bool pop(T *p_value)
        {
            std::unique_lock<std::mutex> l_lock(m_mutex);

            m_cv.wait(l_lock);

            if (m_q.size())
            {
                *p_value = m_q.back();
                m_q.pop_back();
                return (true);
            }
            return (false);
        }

        size_t size()
        {
            std::lock_guard<std::mutex> l_lock(m_mutex);

            return (m_q.size());
        }

        void signal()
        {
            m_cv.notify_one();
        }

        void signal_all()
        {
            m_cv.notify_all();
        }

    private:
        std::deque<T>           m_q;
        std::mutex              m_mutex;
        std::condition_variable m_cv;
        std::atomic<bool>       m_finished;
    };
}

#endif //CPP_PLAZZA_SAFEQ_HPP
