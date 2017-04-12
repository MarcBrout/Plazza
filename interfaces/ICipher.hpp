///
/// \file ICipher.hpp
///

#ifndef CPP_PLAZZA_ICIPHER_HPP
#define CPP_PLAZZA_ICIPHER_HPP

#include <string>
#include <vector>

namespace cipher
{
    ///
    /// \class ICipher interface
    /// \brief Interface for implementing ciphering and deciphering algorithms
    ///
    class ICipher
    {
    public:
        ///
        /// \fn ~ICipher
        /// \brief virtual destructor
        ///
        virtual ~ICipher(){};

        ///
        /// \fn virtual void feed(std::string const& p_str)
        /// \brief method that cipher the input string with its implemented algorithm
        ///     calling multiple time feed will merge the strings together
        /// \param p_str
        virtual void feed(std::string const& p_str) = 0;

        ///
        /// \fn void clear()
        /// \brief clear the strings content
        ///
        virtual void clear() = 0;

        ///
        /// \fn virtual void cipher(const std::string& p_str)
        /// \brief method that cipher the fed string with its implemented algorithm
        /// \return the ciphered string
        virtual std::vector<std::string> cipher() const = 0;

        ///
        /// \fn virtual void decipher(const std::string& p_str)
        /// \brief method that decipher the fed string with its implemented algorithm
        /// \return the deciphered string
        virtual std::vector<std::string> decipher() const = 0;
    };
}

#endif //CPP_PLAZZA_ICIPHER_HPP
