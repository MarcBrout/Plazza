#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
      socketpair(AF_INET, SOCK_STREAM, 0, fd);
      m_fds.push_back(std::make_pair(fd[0], fd[1]));
      return (m_fds.back());
    }

    int SocketInternet::send(int socket, std::string const &msg)
    {
      size_t size = msg.length();
      if (write(socket, msg.c_str(), size) != static_cast<ssize_t>(size))
        return (1);
      return (0);
    }

    int SocketInternet::receive(int socket, std::string const &msg)
    {
      char buffer[4096] = {0};;
      if (recv(socket, buffer, 4095, 0) == 0)
        return (1);
      return (0);
    }

    int SocketInternet::getActivity()
    {
      return (0);
    }

  }
}
