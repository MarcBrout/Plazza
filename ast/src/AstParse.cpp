//
// Created by duhieu_b on 18/04/17.
//

#include "AstParse.hpp"

AstParse::AstParse(std::string &c_comm) : m_command(c_comm), m_graph(AGraphAst<plazza::Type, std::string>(plazza::COMMA, ";"))
{
}

void AstParse::parse()
{
    feedOrder();
    feedGraph();
}

void AstParse::feedOrder()
{
    Splitter l_split;

    l_split.split(m_command, ";");
    l_split.moveTokensTo(m_order);
}

void AstParse::feedGraph()
{
    Splitter l_split;
    for (std::string l_order : m_order)
    {
        l_split.split(l_order);
        l_split.moveTokensTo(m_file);
        for (std::vector<std::string>::iterator it = m_file.begin(); it != m_file.end(); it++)
        {
            if (it + 1 != m_file.end())
                m_graph.addNode(plazza::FILE, *it);
            else
                m_graph.addNode(plazza::ORDER, *it);
        }
        while (!m_graph.validNode())
            m_graph.simpleLinkNode(plazza::ORDER);
        m_file.clear();
    }
}

AGraphAst<plazza::Type, std::string> AstParse::getGraph()
{
    return m_graph;
}
