//
// Created by duhieu_b on 18/04/17.
//

#include "AGraph.hpp"
#include "GraphReader.hpp"

static std::map<std::string, plazza::Information > g_map =
        {
                {"PHONE_NUMBER", plazza::PHONE_NUMBER},
                {"EMAIL_ADDRESS", plazza::EMAIL_ADDRESS},
                {"IP_ADDRESS", plazza::IP_ADDRESS}
        };

void plazza::GraphReader::readGraph(AGraphAst<plazza::Type, std::string> &p_graph)
{
    for (AGraphAst<plazza::Type, std::string>::s_node &l_order : p_graph.getGraph().begin()->s_link)
    {
        for (AGraphAst<plazza::Type, std::string>::s_node &file  : l_order.s_link)
        {
            m_reader.push_back(std::pair<plazza::Information, std::string>(g_map[l_order.s_data.second], file.s_data.second));
        }
    }
}

const std::vector<std::pair<plazza::Information, std::string>> &plazza::GraphReader::getReader() const
{
    return m_reader;
}
