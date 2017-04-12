//
// Created by brout_m on 12/04/17.
//

#ifndef CPP_PLAZZA_ACIPHER_HPP
#define CPP_PLAZZA_ACIPHER_HPP

#include "ICipher.hpp"

namespace cipher
{
    class ACipher : public ICipher
    {
    public:
        void feed(std::string const &p_str);
        void clear();
        ACipher &operator+=(std::string const &p_str);

        virtual std::vector<std::string> cipher() const = 0;
        virtual std::vector<std::string> decipher() const = 0;

    protected:
        std::vector<std::string>    m_strings;
    };
}

#endif //CPP_PLAZZA_ACIPHER_HPP
