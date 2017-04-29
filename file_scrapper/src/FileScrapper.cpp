//
// Created by brout_m on 18/04/17.
//

#include <iostream>
#include "FileScrapper.hpp"

plazza::FileScrapper::FileScrapper(std::string const &p_filename,
                                   plazza::RegexParser *p_regparser) :
        m_fileReader(p_filename),
        m_regParser(p_regparser)
{
    if (!p_regparser)
        throw (std::invalid_argument("Regex parser MUST be provided"));
}

plazza::FileScrapper::~FileScrapper()
{

}

void plazza::FileScrapper::scrapFile()
{
    const std::vector<std::string> &l_rawData = m_fileReader.getRaw();

    for (std::string const& r_str : l_rawData)
    {
        m_regParser->feed(r_str);

        std::vector<std::string> r_reg;
        m_regParser->moveResultsTo(r_reg);

        if (r_reg.size())
            m_results.insert(m_results.end(), r_reg.cbegin(), r_reg.cend());
    }
}

void plazza::FileScrapper::moveResultsTo(std::vector<std::string> &out)
{
    out = std::move(m_results);
}

bool plazza::FileScrapper::isValid()
{
    return (m_fileReader.isOpen());
}

const std::vector<std::string> &plazza::FileScrapper::getResults() const
{
    return m_results;
}

void plazza::FileScrapper::bruteForce(const std::vector<std::string> &p_raw,
                                      cipher::ACipher *p_cipher,
                                      int p_key)
{
    *p_cipher += p_raw;
    p_cipher->setKey(p_key);
    std::vector<std::string> l_results(p_cipher->decipher());
    if (l_results.size())
        m_results.insert(m_results.begin(), l_results.begin(), l_results.end());
    p_cipher->clear();
}