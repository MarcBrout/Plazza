//
// Created by brout_m on 20/04/17.
//

#include <iostream>
#include "FileScrapper.hpp"
#include "Timer.hpp"
#include "ThreadPool.hpp"
#include "ProcessManager.hpp"

void oneThread(threadpool::ThreadPool<std::pair<std::string, plazza::Information>, std::string>::data &p_data)
{
    std::pair<std::string, plazza::Information> l_order;
    plazza::RegexParser l_reg_ip("[0-255].[0-255].[0-255].[0-255]");
    plazza::RegexParser l_reg_email("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
    plazza::RegexParser l_reg_phone("(?:(?:\\+|00)33|0)\\s*[1-9](?:[\\s.-]*\\d{2}){4}");

    std::map<plazza::Information, plazza::RegexParser*> l_map = {
                    {plazza::Information::IP_ADDRESS, &l_reg_ip},
                    {plazza::Information::EMAIL_ADDRESS, &l_reg_email},
                    {plazza::Information::PHONE_NUMBER, &l_reg_phone}
            };

    while (!p_data.s_over)
    {
        if (p_data.s_orderQ.pop(&l_order))
        {
            try
            {
                plazza::FileScrapper w_file_scrapper(l_order.first, l_map[l_order.second]);
                std::vector<std::string> w_results;
                if (w_file_scrapper.isValid())
                {
                    w_file_scrapper.scrapFile();
                    w_file_scrapper.moveResultsTo(w_results);
                    for (std::string &r_str : w_results)
                    {
                        p_data.s_resultQ.push(std::move(r_str));
                    }
                }
            }
            catch (std::exception &err)
            {
                std::cerr << err.what() << std::endl;
            }
        }
    }
}

void oneProcess(int p_socket, size_t p_max_threads)
{
    threadpool::ThreadPool<std::pair<std::string, plazza::Information>, std::string> l_threadp(p_max_threads);
    timer::Timer l_timer(5000);

    (void)p_socket; // TODO: remove

    l_timer.start();
    l_threadp.run(oneThread);
    while (!l_timer.reached())
    {
        std::string w_result;
        m_com->answerAskSizeQueue(); // TODO: code it
        m_com->answerAskOrder(); // TODO: code it -> return pair for execute order

        // TODO: push a pair<string, enum> to l_threadp.pushAction()

        if (l_threadp.orderSize())
            l_timer.reset();

        if (l_threadp.tryPop(&w_result))
        {
          m_com->send(p_socket, w_result);
            // TODO: send results to p_socket
        }
    }
    l_threadp.setOver(true);
}

plazza::ProcessManager::ProcessManager(ICommunication *p_com) :
        m_com(p_com)
{

}

int plazza::ProcessManager::load_balancer(std::vector<std::pair<int, size_t >> const& p_sockets,
                                          size_t p_max_threads)
{
    int l_pos {-1};
    size_t l_smallest {p_max_threads};

    for (size_t r_pos = 0; r_pos < p_sockets.size(); ++r_pos)
    {
        if (p_sockets[r_pos].second < l_smallest)
        {
            l_smallest = r_pos;
        }
    }

    return l_pos;
}

void plazza::ProcessManager::process(std::vector<std::pair<std::string, plazza::Information>> &orders,
                                     size_t p_max_threads)
{
    while (orders.size())
    {
        std::vector<std::pair<int, size_t>> w_child_qs;

        m_com->getAllSizeQueue(w_child_qs);

        int w_socket { load_balancer(w_child_qs, p_max_threads) };
        if (w_socket > 0)
        {
            // TODO: GET ORDER
            m_com->send(w_socket, nullptr);
        }
        else
        {
            int w_new_socket {-1};
           w_new_socket = m_com->addPair().second;

            m_forker.create_child(oneProcess, w_new_socket, p_max_threads);
        }
    }
}

void plazza::ProcessManager::getResults(std::vector<std::string> &results)
{
    // TODO get results from sockets
    m_com->getActivity(); // TODO: push string into resutl
}
