//
// Created by brout_m on 18/04/17.
//

#include <iostream>
#include <mutex>
#include <zconf.h>
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

plazza::NoGUI::NoGUI()
{

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
        Logger::getInstance().enableStdout();
        Logger::getInstance().log(Logger::INFO, l_line);
        l_parser.feedCommand(l_line);
        l_graph_reader.readGraph(l_parser.getGraph());
        l_orders = std::move(l_graph_reader.getReader());
        l_process_manager.process(l_orders, p_thread_max);
      }
    }
    l_process_manager.getResults(l_results);
    for (std::string &r_result : l_results)
    {
      std::cout << r_result << std::endl;
    }
    usleep(5000);
  }
  return (0);
}
