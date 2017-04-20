//
// Created by brout_m on 18/04/17.
//

#include "FileScrapper.hpp"

plazza::FileScrapper::FileScrapper(std::string const &p_filename,
                                   cipher::ACipher *p_cipher) :
        m_file(p_filename, std::iostream::in),
        m_cipher(p_cipher)
{
}

plazza::FileScrapper::~FileScrapper()
{

}

void plazza::FileScrapper::scrapFile()
{

}

void plazza::FileScrapper::moveResultsTo(std::vector<std::string> &out)
{
    out = std::move(m_results);
}
