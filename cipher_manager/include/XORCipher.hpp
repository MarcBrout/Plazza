//
// Created by brout_m on 12/04/17.
//

#ifndef CPP_PLAZZA_XORCIPHER_HPP
#define CPP_PLAZZA_XORCIPHER_HPP

#include "ACipher.hpp"

namespace cipher
{
    class XORCipher : public ACipher
    {
    public:
        // Constructors and operator= Overloads
        ~XORCipher();
        XORCipher(int p_length = 10);
        XORCipher(XORCipher const &xorCipher) = default;
        XORCipher(XORCipher &&xorCipher) = default;
        XORCipher &operator=(XORCipher const &xorCipher) = default;
        XORCipher &operator=(XORCipher &&xorCipher) = default;

        // Methods
        std::vector<std::string> cipher() const;
        std::vector<std::string> decipher() const;
        void setKey(size_t p_key);

    private:
        size_t                      m_key;

        // Private methods
        void XORCipherString(std::string &p_str) const;
    };
}

#endif //CPP_PLAZZA_XORCIPHER_HPP
