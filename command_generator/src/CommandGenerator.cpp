//
// Created by brout_m on 14/04/17.
//

#include <algorithm>
#include "CommandGenerator.hpp"

CommandGenerator::CommandGenerator(std::vector<std::string> const &p_allowed) :
        m_splitter(),
        m_cmd({}),
        m_order({}),
        m_allowed(p_allowed)
{
}

CommandGenerator::~CommandGenerator()
{

}

std::string CommandGenerator::getCmd() const
{
    std::string l_cmd {""};

    for (size_t f_cmdIndex = 0; f_cmdIndex < m_cmd.size(); ++f_cmdIndex)
    {
        for (size_t f_strIndex = 0; f_strIndex < m_cmd[f_cmdIndex].size();
             ++f_strIndex)
        {
            l_cmd += m_cmd[f_cmdIndex][f_strIndex] + " ";
        }
        l_cmd += m_order[f_cmdIndex];
        if (f_cmdIndex < m_cmd.size() - 1)
            l_cmd += "; ";
    }

    return l_cmd;
}

void CommandGenerator::feed(const std::string &p_content,
                            const std::string &p_flag)
{
    if (std::find(m_allowed.cbegin(), m_allowed.cend(), p_flag) != m_allowed.cend())
    {
        m_splitter.split(p_content, " \n\t");
        m_cmd.push_back(m_splitter.getTokens());
        m_order.push_back(p_flag);
        m_splitter.clear();
    }
}

void CommandGenerator::clear()
{
    m_cmd.clear();
    m_splitter.clear();
}
