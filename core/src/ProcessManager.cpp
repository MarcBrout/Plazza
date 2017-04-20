//
// Created by brout_m on 20/04/17.
//

#include <iostream>
#include "FileScrapper.hpp"
#include "Timer.hpp"
#include "ThreadPool.hpp"
#include "ProcessManager.hpp"

void scrap_file(threadpool::ThreadPool<std::pair<std::string, plazza::Information>, std::string>::data &p_data)
{
    std::pair<std::string, plazza::Information> l_order;
    std::map<plazza::Information, plazza::RegexParser> l_map =
            {
                    {plazza::Information::IP_ADDRESS,
                            plazza::RegexParser("[0-255].[0-255].[0-255].[0-255]")},
                    {plazza::Information::EMAIL_ADDRESS,
                            plazza::RegexParser("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+")},
                    {plazza::Information::PHONE_NUMBER,
                            plazza::RegexParser("(?:(?:\\+|00)33|0)\\s*[1-9](?:[\\s.-]*\\d{2}){4}")}
            };

    while (!p_data.s_over)
    {
        if (p_data.s_orderQ.pop(&l_order))
        {
            try
            {
                plazza::FileScrapper w_file_scrapper(l_order.first, &l_map[l_order.second]);
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

    l_timer.start();
    l_threadp.run(scrap_file);
    while (!l_timer.reached())
    {
        std::string w_result;
        // TODO: read p_socket and send threadpool qsize
        // TODO: read p_socket and get string + enum

        // l_threadp.pushAction()

        if (l_threadp.orderSize())
            l_timer.reset();

        if (l_threadp.tryPop(&w_result))
        {
            // TODO: send results to p_socket
        }
    }
    l_threadp.setOver(true);
}

plazza::ProcessManager::ProcessManager(ICommunication *p_com) :

{

}
