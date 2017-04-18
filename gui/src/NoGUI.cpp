//
// Created by brout_m on 18/04/17.
//

#include <iostream>
#include <mutex>
#include <zconf.h>
#include "NoGUI.hpp"

void read_cin(threadpool::ThreadPool<bool, std::string>::Data &p_data)
{
    while (!p_data.s_over)
    {
        std::string l_line;

        std::getline(std::cin, l_line);

        if (std::cin.eof())
        {
            p_data.s_resultQ.push("");
            break;
        }
        else if (!l_line.empty())
        {
            p_data.s_resultQ.push(std::move(l_line));
        }
        std::cin.clear();
        std::cout.clear();
    }
}

plazza::NoGUI::NoGUI()
{

}

int plazza::NoGUI::run()
{
    std::string l_line;

    m_threadpool.run(read_cin);
    while (!m_threadpool.isOver())
    {
        if (m_threadpool.getResults().tryPop(&l_line))
        {
            if (l_line.empty())
            {
                m_threadpool.setOver(true);
            }
            else
            {
              std::cout << l_line << std::endl;
            }
            //TODO : PARSE STRING AND EXECUTE COMMAND HERE
        }
        usleep(5000);
    }
    return (0);
}
