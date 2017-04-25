//
// Created by duhieu_b on 18/04/17.
//

#include <iostream>
#include "AstParse.hpp"

static std::vector<std::string> g_order = {
        "PHONE_NUMBER",
        "EMAIL_ADDRESS",
        "IP_ADDRESS"
};

plazza::AstParse::AstParse() :
        m_graph(AGraphAst<plazza::Type, std::string>(plazza::COMMA, ";"))
{
}

void plazza::AstParse::feedCommand(std::string const& p_command)
{
    Splitter l_split;

    l_split.split(p_command, ";");
    l_split.moveTokensTo(m_order);
    l_split.clear();
    feedGraph();
    m_order.clear();
}

void plazza::AstParse::feedGraph()
{
    Splitter l_split;
    for (std::string l_order : m_order)
    {
        l_split.split(l_order);
        l_split.moveTokensTo(m_file);
        try {
            checkError();
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            m_file.clear();
            continue;
        }
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

AGraphAst<plazza::Type, std::string> &plazza::AstParse::getGraph()
{
    return m_graph;
}

void plazza::AstParse::checkError()
{
    if (m_file.size() < 2)
        throw std::invalid_argument("Order usage: FILE + INFORMATION_TO_GET");
    if (std::find(g_order.begin(), g_order.end(), m_file.back()) == g_order.end())
        throw std::invalid_argument("Order must have an INFORMATION_TO_GET");
    size_t count(0);
    for (std::string file : m_file)
    {
        if (std::find(g_order.begin(), g_order.end(), file) != g_order.end())
            count++;
    }
    if (count > 1)
        throw std::invalid_argument("Order must have just one INFORMATION_TO_GET");
}

void plazza::AstParse::clear()
{
    m_graph.clear();
}
