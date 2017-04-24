#include "Logger.hpp"

namespace plazza
{
  Logger::~Logger()
  {
    for (std::size_t i = 0; i < m_logFiles.size(); i++)
    {
      m_logFiles[i].close();
    }
  }
  
  void Logger::addFile(std::string const &fileName)
  {
    std::ofstream file;
    file.open(fileName);
    m_logFiles.push_back(std::move(file));
  }

  void Logger::enableStdout()
  {
    m_isStdout = true;
  }

  void Logger::disableStdout()
  {
    m_isStdout = false;
  }

  void Logger::log(LogLevel level, std::string const &msg)
  {
    if (level < m_level)
      return ;
    if (m_isStdout)
      log_stdout(msg);
    if (m_logFiles.size() > 0)
      log_file(msg);
  }

  void Logger::log_stdout(std::string const &msg)
  {
    std::cout << "[log]" << msg << std::endl;
  }

  void Logger::log_file(std::string const &msg)
  {
    for (std::size_t i = 0; i < m_logFiles.size(); i++)
    {
      m_logFiles[i] << "[log]" << msg << "\n";
    }
  }
}
