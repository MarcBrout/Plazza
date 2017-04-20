//
// Created by brout_m on 19/04/17.
//

#include "RegexParser.hpp"

plazza::RegexParser::RegexParser(const std::string &p_reg) :
        m_regex(p_reg)
{

}

bool plazza::RegexParser::feed(std::string const &p_str)
{
    std::smatch l_feed_match;
    bool        find {false};

    for (std::sregex_iterator it = std::sregex_iterator(p_str.begin(), p_str.end(), m_regex);
            it != std::sregex_iterator();
            ++it)
    {
        if (!find)
            find = true;
        std::smatch r_match(*it);
        m_results.push_back(r_match.str());
    }
    return (find);
}

void plazza::RegexParser::moveResultsTo(std::vector<std::string> &p_out)
{
    p_out = std::move(m_results);
}

std::vector<std::string> plazza::RegexParser::getResultsCopy() const
{
    return m_results;
}

const std::vector<std::string> &plazza::RegexParser::getResults() const
{
    return m_results;
}

