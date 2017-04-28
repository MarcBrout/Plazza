//
// Created by duhieu_b on 18/04/17.
//

#ifndef CPP_PLAZZA_ASTPARSE_HPP
#define CPP_PLAZZA_ASTPARSE_HPP

#include "AGraph.hpp"
#include "Enums.hpp"
#include "Splitter.hpp"

namespace plazza
{
    class AstParse
    {
    private:
        std::vector<std::string> m_order;
        std::vector<std::string> m_file;
        AGraphAst<plazza::Type, std::string> m_graph;

        void checkError();
        int feedGraph();

    public:
        AstParse();
        ~AstParse() {};
        AGraphAst<plazza::Type, std::string> &getGraph();
        int feedCommand(std::string const& p_command);
        void clear();
    };
}

#endif //CPP_PLAZZA_ASTPARSE_HPP
