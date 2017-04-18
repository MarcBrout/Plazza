#ifndef ICOMMUNICATION_HPP_
# define ICOMMUNICATION_HPP_

#include <string>

class ICommunication
{
  public:
    virtual ~ICommunication(){};
    virtual int send(int socket, std::string const &msg) = 0;
    virtual int receive(int socket, std::string const &msg) = 0;
    virtual int get_activity() = 0;
};

#endif
