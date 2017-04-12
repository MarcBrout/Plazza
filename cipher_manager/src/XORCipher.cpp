//
// Created by brout_m on 12/04/17.
//

#include <algorithm>
#include "XORCipher.hpp"

cipher::XORCipher::XORCipher(int p_length) :
        m_key(static_cast<size_t >(std::rand() % p_length))
{
}

cipher::XORCipher::~XORCipher()
{
}

void cipher::XORCipher::XORCipherString(std::string &p_str) const
{
    std::for_each(p_str.begin(), p_str.end(),
                  [this, &p_str](char &p_char)
                  {
                      p_char ^= this->m_key;
                  });
}

std::vector<std::string> cipher::XORCipher::decipher() const
{
    std::vector<std::string> l_cpy = m_strings;

    std::for_each(l_cpy.begin(), l_cpy.end(),
                  [this](std::string &p_str)
                  {
                      XORCipherString(p_str);
                  });
    return l_cpy;
}

std::vector<std::string> cipher::XORCipher::cipher() const
{
    return decipher();
}

void cipher::XORCipher::setKey(size_t p_key)
{
    m_key = p_key;
}