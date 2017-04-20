//
// Created by duhieu_b on 18/04/17.
//

#ifndef CPP_PLAZZA_ASTPARSE_HPP
#define CPP_PLAZZA_ASTPARSE_HPP

#include "AGraph.hpp"
#include "Enums.hpp"
#include "Splitter.hpp"

class AstParse
{
private:
    std::string m_command;
    std::vector<std::string> m_order;
    std::vector<std::string> m_file;
    AGraphAst<plazza::Type, std::string> m_graph;

    void feedOrder();
    void feedGraph();
public:
    AstParse(std::string &comm);
    ~AstParse() {}
    void parse();
    AGraphAst<plazza::Type, std::string> getGraph();

};


#endif //CPP_PLAZZA_ASTPARSE_HPP
