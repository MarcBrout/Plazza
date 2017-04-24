#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

#include <string>
#include <vector>

namespace plazza
{
  namespace com
  {
    class ICommunication
    {
      public:
        virtual ~ICommunication(){};
        virtual int send(int socket, std::string const &msg) = 0;
        virtual int getActivity(std::vector<std::string> &) = 0;
        virtual std::pair<int, int> &addPair() = 0;
        virtual int sendAll(std::string const &msg) = 0;
        virtual int getAllSizeQueue(std::vector<std::pair<int, std::size_t> > &) = 0;
        virtual int readFromMaster(int sock, std::size_t size, std::string &res) = 0;
    };
  }
}

#endif
