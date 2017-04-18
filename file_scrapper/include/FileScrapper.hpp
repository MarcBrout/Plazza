//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_FILESCRAPPER_HPP
#define CPP_PLAZZA_FILESCRAPPER_HPP

#include <fstream>
#include "ACipher.hpp"

namespace plazza
{
    class FileScrapper
    {
    public:
        FileScrapper(std::string const& p_filename, cipher::ACipher *p_cipher);
        ~FileScrapper();
        void scrapFile();
        void plazza::FileScrapper::moveResultsTo(std::vector<std::string> &out);

    private:
        std::ifstream               m_file;
        cipher::ACipher            *m_cipher;
        std::vector<std::string>    m_results;

        FileScrapper() = delete;
        FileScrapper(FileScrapper const&) = delete;
        FileScrapper(FileScrapper &&) = delete;
        FileScrapper &operator=(FileScrapper const&) = delete;
        FileScrapper &operator=(FileScrapper &&) = delete;
    };
}

#endif //CPP_PLAZZA_FILESCRAPPER_HPP
