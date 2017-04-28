//
// Created by brout_m on 18/04/17.
//

#include <iostream>
#include <mutex>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include "AstParse.hpp"
#include "GraphReader.hpp"
#include "ProcessManager.hpp"
#include "NoGUI.hpp"
#include "SocketInternet.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

plazza::NoGUI::NoGUI() :
        m_over(false)
{

}

int readSelect(std::string &p_output)
{
    char buffer[4096] = {0};
    struct timeval l_time {0, 0};
    int l_rd {0};
    fd_set  l_fds;

    FD_ZERO(&l_fds);
    FD_SET(0, &l_fds);

    l_time.tv_sec = 0;
    l_time.tv_usec = 100000;

    l_rd = select(1, &l_fds, NULL, NULL, &l_time);
    if (l_rd < 0)
    {
        return (1);
    }
    else if (!l_rd)
    {
        return (-1);
    }
    else
    {
        if (FD_ISSET(0, &l_fds))
        {
            if ((l_rd = read(0, buffer, 4095)) <= 0)
            {
                return (0);
            }
            buffer[l_rd - 1] = 0;
            p_output = buffer;
        }
        return (0);
    }
}

int outputCheck(std::string &p_line)
{
    if (p_line.find_first_of(" \t") == std::string::npos)
        return 0;
    if (p_line.substr(0, p_line.find_first_of(" \t")) == "enable")
    {
        if (p_line.substr(p_line.find_first_of(" \t") + 1) == "file")
            plazza::Logger::getInstance().enableFileOut();
        else if (p_line.substr(p_line.find_first_of(" \t") + 1) == "stdout")
            plazza::Logger::getInstance().enableStdout();
        else
            return 0;
        return 1;
    }
    else if (p_line.substr(0, p_line.find_first_of(" \t")) == "disable")
    {
        if (p_line.substr(p_line.find_first_of(" \t") + 1) == "file")
            plazza::Logger::getInstance().disableFileOut();
        else if (p_line.substr(p_line.find_first_of(" \t") + 1) == "stdout")
            plazza::Logger::getInstance().disableStdout();
        else
            return 0;
        return 1;
    }
    return (0);
}

int plazza::NoGUI::run(size_t p_thread_max)
{
    std::string l_line;
    std::vector<std::string> l_cuttedLine;
    plazza::com::SocketInternet sock;
    plazza::ProcessManager l_process_manager(&sock);
    std::vector<std::string> l_results;
    timer::Timer   l_timer(5000);
    Splitter    l_splitter;

    int bit;
    int ret {0};

    l_timer.start();
    while (!m_over)
    {
        if (readSelect(l_line) == 1 || l_timer.reached())
        {
            m_over = true;
        }
        else if (l_line.size() && !ret)
        {
            l_splitter.split(l_line, "\n");
            l_splitter.moveTokensTo(l_cuttedLine);

            if (l_cuttedLine.size())
            {
                for (std::string r_line : l_cuttedLine)
                {
                    if (r_line == "exit" || r_line == "quit")
                        return (ret);

                    if (outputCheck(r_line))
                    {
                        r_line.clear();
                        continue;
                    }

                    plazza::AstParse l_parser;
                    plazza::GraphReader l_graph_reader;
                    std::vector<std::pair<std::string, plazza::Information>> l_orders;

                    Logger::getInstance().log(Logger::INFO, r_line);
                    if (l_parser.feedCommand(r_line)) {
                        ret = 1;
                        break;
                    }

                    l_graph_reader.readGraph(l_parser.getGraph());
                    l_orders = std::move(l_graph_reader.getReader());
                    l_process_manager.process(l_orders, p_thread_max);
                }
                l_cuttedLine.clear();
                if (ret == 1)
                    break;
            }
            l_line.clear();
        }

        if (waitpid(-1, &bit, WNOHANG) == 0)
            l_timer.reset();

        l_process_manager.getResults(l_results);
        for (std::string &r_result : l_results)
        {
            (void)r_result;
            //std::cout << r_result << std::endl;
        }
        l_results.clear();
        usleep(5000);
    }
    while (waitpid(-1, &bit, WNOHANG) == 0)
    {
        usleep(10);
    }
    return (ret);
}
