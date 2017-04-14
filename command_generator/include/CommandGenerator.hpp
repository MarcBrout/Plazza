//
// Created by brout_m on 14/04/17.
//

#ifndef CPP_PLAZZA_COMMANDGENERATOR_HPP
#define CPP_PLAZZA_COMMANDGENERATOR_HPP

#include "Splitter.hpp"

class CommandGenerator
{
public:
    CommandGenerator(std::vector<std::string> const &p_allowed);
    ~CommandGenerator();
    void feed(const std::string &p_content, const std::string &p_flag);
    std::string getCmd() const;
    void clear();

private:
    Splitter                                            m_splitter;
    std::vector<std::vector<std::string>>               m_cmd;
    std::vector<std::string>                            m_order;
    std::vector<std::string>                            m_allowed;
    CommandGenerator() = delete;
};


#endif //CPP_PLAZZA_COMMANDGENERATOR_HPP
