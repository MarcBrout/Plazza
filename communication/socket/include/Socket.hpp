#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include "ICommunication.hpp"
#include <vector>

namespace plazza
{
  namespace com
  {
    class Socket: public ICommunication
    {
      public:
        Socket();
        virtual ~Socket();
        virtual int send(int socket, std::string const &msg);
        virtual int receive(int socket, std::string const &msg);
        virtual int getActivity();
      private:
        std::vector<int> m_fds;
        int m_master;
        int m_maxClient;
    };
  }
}

#endif
