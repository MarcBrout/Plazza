//
// Created by brout_m on 12/04/17.
//

#include <algorithm>
#include "CesarCipher.hpp"

cipher::CesarCipher::~CesarCipher()
{
}

cipher::CesarCipher::CesarCipher(int p_length) :
        m_shift(p_length % 26)
{
}

void cipher::CesarCipher::CesarCipherString(std::string &p_str) const
{
    std::for_each(p_str.begin(), p_str.end(),
                  [this](char &p_char)
                  {
                      p_char += m_shift;
                  });
}

void cipher::CesarCipher::CesarDecipherString(std::string &p_str) const
{
    std::for_each(p_str.begin(), p_str.end(),
                  [this](char &p_char)
                  {
                      p_char -= m_shift;
                  });

}

std::vector<std::string> cipher::CesarCipher::doAction(cipher::CesarCipher::t_cipher_action action) const
{
    std::vector<std::string> l_cpy = m_strings;

    std::for_each(l_cpy.begin(), l_cpy.end(),
                  [this, &action](std::string &p_str)
                  {
                      (this->*action)(p_str);
                  });
    return l_cpy;
}

std::vector<std::string> cipher::CesarCipher::cipher() const
{
    return doAction(&cipher::CesarCipher::CesarCipherString);
}

std::vector<std::string> cipher::CesarCipher::decipher() const
{
    return doAction(&cipher::CesarCipher::CesarDecipherString);
}

void cipher::CesarCipher::setKey(int p_key)
{
    m_shift = p_key % 26;
}
