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
        virtual std::pair<int, int> &addPair();
        virtual int sendAll(std::string const &msg);
        virtual int getAllSizeQueue(std::vector<std::pair<int, std::size_t> > &);
        virtual int answerAskSizeQueue(); // if parent ask for size queue -> answer him
        virtual int answerAskOrder(); // if order receive, execute it
      private:
        std::vector<std::pair<int, int> > m_fds;
        int m_master;
        int m_maxClient;
    };
  }
}

#endif
