#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

#include <string>
#include <vector>

class ICommunication
{
  public:
    virtual ~ICommunication(){};
    virtual int send(int socket, std::string const &msg) = 0;
    virtual int receive(int socket, std::string const &msg) = 0;
    virtual int get_activity() = 0;
    virtual std::pair<int, int> &addPair() = 0;
    virtual int sendAll(std::string const &msg) = 0;
    virtual int getAllSizeQueue(std::vector<std::pair<int, std::size_t> > &) = 0;
    virtual int answerAskSizeQueue(int socket, std::size_t) = 0; // if parent ask for size queue -> answer him
    virtual int answerAskOrder() = 0; // if order receive, execute it
};

#endif
