//
// Created by brout_m on 12/04/17.
//

#ifndef CPP_PLAZZA_CESARCIPHER_HPP
#define CPP_PLAZZA_CESARCIPHER_HPP

#include "ACipher.hpp"

namespace cipher 
{
    class CesarCipher : public ACipher
    {
    public:
        ~CesarCipher();
        CesarCipher(int p_length = 10);
        CesarCipher(CesarCipher const &xorCipher) = default;
        CesarCipher(CesarCipher &&xorCipher) = default;
        CesarCipher &operator=(CesarCipher const &xorCipher) = default;
        CesarCipher &operator=(CesarCipher &&xorCipher) = default;
        std::vector<std::string> cipher() const;
        std::vector<std::string> decipher() const;
        void setKey(int p_key);

    private:
        int                         m_shift;

        // Methods
        typedef void (cipher::CesarCipher::*t_cipher_action)(std::string &) const;
        std::vector<std::string> doAction(t_cipher_action action) const;
        void CesarCipherString(std::string &p_str) const;
        void CesarDecipherString(std::string &p_str) const;
    };
}

#endif //CPP_PLAZZA_CESARCIPHER_HPP
