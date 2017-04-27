#ifndef LOGGER_HPP_
# define LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <vector>

namespace plazza
{
  class Logger
  {
    public:
      enum LogLevel
      {
        INFO = 0,
        ERROR
      };

    public:
      static Logger& getInstance()
      {
        static Logger instance;
        return instance;
      }

    public:
      Logger():m_level(INFO), m_isStdout(false){}
      ~Logger();
      Logger(Logger const&) = delete;
      void operator=(Logger  const&)  = delete;
      void addFile(std::string const &fileName);
      void enableStdout();
      void disableStdout();
      void enableFileOut();
      void disableFileOut();
      void log(LogLevel, std::string const &msg);
      void logResult(std::string const &);

    private:
      void log_stdout(std::string const &msg);
      void log_file(std::string const &msg);

    private:
      LogLevel m_level;
      bool m_isStdout;
      bool m_isFileOut;
      std::vector<std::ofstream> m_logFiles;
  };
}

#endif
