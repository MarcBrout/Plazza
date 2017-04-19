//
// Created by brout_m on 12/04/17.
//

#include "ACipher.hpp"


void cipher::ACipher::feed(std::string const &p_str)
{
    m_strings.push_back(p_str);
}

void cipher::ACipher::clear()
{
    m_strings.clear();
}

cipher::ACipher &cipher::ACipher::operator+=(std::string const &p_str)
{
    m_strings.push_back(p_str);
    return *this;
}

cipher::ACipher &cipher::ACipher::operator+=(std::vector<std::string> const &p_vec)
{
    m_strings.insert(m_strings.end(), p_vec.cbegin(), p_vec.cend());
    return *this;
}
