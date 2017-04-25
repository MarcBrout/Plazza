#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include "SocketInternet.hpp"
#include "Logger.hpp"

namespace plazza
{
  namespace com
  {
    SocketInternet::SocketInternet()
    {
    }

    SocketInternet::~SocketInternet()
    {
    }

    std::pair<int, int> &SocketInternet::addPair()
    {
      int fd[2];
      socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
      m_fds.push_back(std::make_pair(fd[0], fd[1]));
      return (m_fds.back());
    }

    int SocketInternet::sendAll(std::string const &msg)
    {
      for (unsigned int i = 0; i < m_fds.size(); i++)
      {
        //std::cout << "SENDALL:'" << msg << "' TO SOCKET: " << m_fds[i].first << std::endl;
        if (write(m_fds[i].first, msg.c_str(), msg.length()) != static_cast<ssize_t>(msg.length()))
        {
          return (1);
        }
      }
      return (0);
    }

    int SocketInternet::send(int socket, std::string const &msg)
    {
      //plazza::Logger::getInstance().log(plazza::Logger::INFO, "SEND TO");
      //std::cout << "SEND:'" << msg << "' TO SOCKET: " << socket << std::endl;
      size_t size = msg.length();
      if (write(socket, msg.c_str(), size) != static_cast<ssize_t>(size))
        return (1);
      return (0);
    }

    int SocketInternet::getAllSizeQueue(std::vector<std::pair<int, std::size_t> > &vec)
    {
      char buffer[1024] = {0};
      int len;

      for (size_t i = 0; i < m_fds.size(); i++)
      {
        send(m_fds[i].first, "size");
        std::string res;
        len = read(m_fds[i].first, buffer, 1023);
        buffer[len] = 0;
        res = buffer;
        std::size_t size(std::atol(res.c_str()));
        vec.push_back(std::make_pair(m_fds[i].first, size));
      }
      return (0);
    }

    int SocketInternet::readFromMaster(int sock, std::size_t size, std::string &res)
    {
      int activity;
      int len;
      char buffer[1024] = {0};
      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 1;
      std::string check;
      fd_set readfds;
      FD_ZERO(&readfds);
      FD_SET(sock, &readfds);

      activity = select(sock + 1, &readfds, NULL, NULL, &timeout);
      if (activity < 0)
      {
        perror("Select");
        return (1);
      }
      else if (!activity)
      {
        //std::cerr << "Timed out" << std::endl;
        //TODO: log.error();
      }
      else
      {
        if (FD_ISSET(sock, &readfds)) 
        {
          if ((len = read(sock, buffer, 1023)) == 0)
          {
            close(sock);
            return (1);
          }
          buffer[len] = 0;
          check = buffer;
          if (check == "size")
          {
            std::stringstream stream;
            stream << size;
            plazza::Logger::getInstance().log(plazza::Logger::INFO, "[Child] Master asked for size");
            send(sock, stream.str());
            return (0);
          }
          else if (std::strlen(buffer))
          {
            plazza::Logger::getInstance().log(plazza::Logger::INFO, "[Child] Master gave order");
            res = buffer;
            return (1);
          }
        }
      }
      return (-1);
    }

    int SocketInternet::getActivity(std::vector<std::string> &results)
    {
      int activity, valread , sd;
      int max_sd = 0;
      fd_set readfds;
      char buffer[1024];
      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 1;

      FD_ZERO(&readfds);
      for (unsigned int i = 0; i < m_fds.size(); i++)
      {
        sd = m_fds[i].first;
        if (sd > 0)
          FD_SET(sd, &readfds);
        if (sd > max_sd)
          max_sd = sd;
      }

      /*do
        {
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        } while (activity == -1 && errno == EINTR);*/
      activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
      if (activity < 0)
      {
        perror("Select");
        return (1);
      }
      else if (!activity)
      {
        //std::cerr << "Timed out" << std::endl;
        //TODO: log.error();
      }
      else
      {
        for (unsigned int i = 0; i < m_fds.size(); i++) 
        {
          sd = m_fds[i].first;
          if (FD_ISSET(sd , &readfds)) 
          {
            if ((valread = read(sd, buffer, 1024)) == 0)
            {
              //std::cerr << "client disconnected" << std::endl;
              close(sd);
              m_fds.erase(m_fds.begin() + i);
              //CLOSE FROM VECTOR -> REMOVE PAIR
            }
            else
            {
              buffer[valread] = '\0';
              //plazza::Logger::getInstance().log(plazza::Logger::INFO, buffer);
              results.push_back(std::move(std::string(buffer)));
            }
          }
        }
      }
      return (0);
    }
  }
}
