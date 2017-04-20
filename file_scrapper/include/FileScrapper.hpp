//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_FILESCRAPPER_HPP
#define CPP_PLAZZA_FILESCRAPPER_HPP

#include <fstream>
#include <XORCipher.hpp>
#include <CesarCipher.hpp>
#include "ACipher.hpp"
#include "FileReader.hpp"
#include "RegexParser.hpp"

namespace plazza
{
    class FileScrapper
    {
    public:
        FileScrapper(std::string const& p_filename,
                     plazza::RegexParser *p_regparser);
        ~FileScrapper();
        void scrapFile();
        void moveResultsTo(std::vector<std::string> &out);
        const std::vector<std::string> &getResults() const;
        bool isValid();

    private:
        FileReader                  m_fileReader;
        plazza::RegexParser        *m_regParser;
        std::vector<std::string>    m_results;
        cipher::XORCipher           m_XORCipher;
        cipher::CesarCipher         m_CesarCipher;

        void bruteForce(const std::vector<std::string> &p_raw,
                        cipher::ACipher *p_cipher,
                        int p_key);

        // Deleted methods
        FileScrapper() = delete;
        FileScrapper(FileScrapper const&) = delete;
        FileScrapper(FileScrapper &&) = delete;
        FileScrapper &operator=(FileScrapper const&) = delete;
        FileScrapper &operator=(FileScrapper &&) = delete;
    };
}

#endif //CPP_PLAZZA_FILESCRAPPER_HPP
