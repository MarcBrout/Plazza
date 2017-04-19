//
// Created by brout_m on 19/04/17.
//

#include "FileReader.hpp"

plazza::FileReader::FileReader(const std::string &p_filename) :
        m_file(p_filename, std::iostream::in)
{
    if (!m_file.is_open())
        throw (std::runtime_error("Error while opening file : " + p_filename));

    std::string line;

    while (std::getline(m_file, line))
    {
        m_raw.push_back(std::move(line));
    }
}

plazza::FileReader::~FileReader()
{
    if (m_file.is_open())
        m_file.close();
}


const std::vector<std::string> &plazza::FileReader::getRaw() const
{
    return m_raw;
}

std::vector<std::string> plazza::FileReader::getRawCopy() const
{
    return m_raw;
}

bool plazza::FileReader::isOpen() const {
    return (m_file.is_open());
}

void plazza::FileReader::moveRawTo(std::vector<std::string> &p_out)
{
    p_out = std::move(m_raw);
}