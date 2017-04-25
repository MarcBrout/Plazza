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
                return (1);
            }
            buffer[l_rd - 1] = 0;
            p_output = buffer;
        }
        return (0);
    }
}

int plazza::NoGUI::run(size_t p_thread_max)
{
  std::string l_line;
  plazza::com::SocketInternet sock;
  plazza::AstParse    l_parser;
  plazza::GraphReader l_graph_reader;
  plazza::ProcessManager  l_process_manager(&sock);
  std::vector<std::pair<std::string, plazza::Information>> l_orders;
  std::vector<std::string> l_results;
  int bite;

  while (!m_over)
  {
    if (readSelect(l_line) == 1)
    {
        m_over = true;
    }
    else if (l_line.size())
    {
        Logger::getInstance().log(Logger::INFO, l_line);
        l_parser.feedCommand(l_line);
        l_line.clear();
        l_graph_reader.clear();
        l_graph_reader.readGraph(l_parser.getGraph());
        l_orders.clear();
        l_orders = std::move(l_graph_reader.getReader());
        l_process_manager.process(l_orders, p_thread_max);
    }

    waitpid(-1, &bite, WNOHANG);
    l_process_manager.getResults(l_results);
    for (std::string &r_result : l_results)
    {
      std::cout << r_result << std::endl;
    }
    l_results.clear();
    usleep(5000);
  }
  std::cout << "Quit biatch !" << std::endl;
  return (0);
}
