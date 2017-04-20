//
// Created by brout_m on 19/04/17.
//

#ifndef CPP_PLAZZA_REGEXPARSER_HPP
#define CPP_PLAZZA_REGEXPARSER_HPP


#include <regex>

namespace plazza
{
    class RegexParser
    {
    public:
        RegexParser(std::string const& p_reg);
        bool feed(std::string const& p_str);
        void moveResultsTo(std::vector<std::string> &p_out);
        std::vector<std::string> getResultsCopy() const;
        const std::vector<std::string> &getResults() const;

    private:
        std::regex                  m_regex;
        std::vector<std::string>    m_results;
    };
}

#endif //CPP_PLAZZA_REGEXPARSER_HPP
