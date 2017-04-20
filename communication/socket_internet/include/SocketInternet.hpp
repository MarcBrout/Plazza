#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include "ICommunication.hpp"
#include <vector>

namespace plazza
{
  namespace com
  {
    class SocketInternet: public ICommunication
    {
      public:
        SocketInternet();
        virtual ~SocketInternet();
        virtual int send(int socket, std::string const &msg);
        virtual int receive(int socket, std::string const &msg);
        virtual int getActivity();
        std::pair<int, int> &addPair();
        int sendAll(std::string const &msg);
      private:
        std::vector<std::pair<int, int> > m_fds;
        int m_master;
        int m_maxClient;
    };
  }
}

#endif
