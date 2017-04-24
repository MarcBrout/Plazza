#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <string>
#include "SocketInternet.hpp"

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
        if (write(m_fds[i].first, msg.c_str(), msg.length()) != static_cast<ssize_t>(msg.length()))
        {
          return (1);
        }
      }
      return (0);
    }

    int SocketInternet::send(int socket, std::string const &msg)
    {
      size_t size = msg.length();
      if (write(socket, msg.c_str(), size) != static_cast<ssize_t>(size))
        return (1);
      return (0);
    }

    int SocketInternet::receive(int socket, std::string &msg)
    {
      char buffer[4096] = {0};;
      if (recv(socket, buffer, 4095, 0) == 0)
        return (1);
      msg = buffer;
      return (0);
    }

    int SocketInternet::getAllSizeQueue(std::vector<std::pair<int, std::size_t> > &vec)
    {
      for (size_t i = 0; i < m_fds.size(); i++)
      {
        send(m_fds[i].first, "size");
        std::string res;
        receive(m_fds[i].first, res);
        std::size_t size(std::atol(res.c_str()));
        vec.push_back(std::make_pair(m_fds[i].first, size));
      }
      return (0);
    }

    int SocketInternet::answerAskSizeQueue(int sock, std::size_t size)
    {
      std::string res;
      receive(sock, res);
      if (res == "size")
      {
        std::stringstream stream;
        stream << size;
        send(sock, stream.str());
      }
      return (0);
    }

    int SocketInternet::answerAskOrder()
    {
      return (0);
    }

    int SocketInternet::getActivity()
    {
      int activity, valread , sd;
      int max_sd = 0;
      fd_set readfds;
      char buffer[1024];

      FD_ZERO(&readfds);
      for (unsigned int i = 0; i < m_fds.size(); i++)
      {
        sd = m_fds[i].first;
        if (sd > 0)
          FD_SET(sd, &readfds);
        if (sd > max_sd)
          max_sd = sd;
      }

      do
      {
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
      } while (activity == -1 && errno == EINTR);
      if (activity < 0)
      {
        perror("Select");
        return (1);
      }
      else if (!activity)
      {
        std::cerr << "Timed out" << std::endl;
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
              std::cerr << "client disconnected" << std::endl;
              close(sd);
              //CLOSE FROM VECTOR -> REMOVE PAIR
            }
            else
            {
              buffer[valread] = '\0';
            }
          }
        }
      }
      return (0);
    }
  }
}
