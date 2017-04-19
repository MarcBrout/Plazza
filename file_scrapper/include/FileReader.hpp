//
// Created by brout_m on 19/04/17.
//

#ifndef CPP_PLAZZA_FILEREADER_HPP
#define CPP_PLAZZA_FILEREADER_HPP

#include <string>
#include <fstream>
#include <vector>

namespace plazza
{
    class FileReader
    {
    public:
        FileReader(const std::string &p_filename);
        ~FileReader();
        std::vector<std::string> getRawCopy() const;
        const std::vector<std::string> &getRaw() const;
        void moveRawTo(std::vector<std::string> &p_out);
        bool isOpen() const;

    private:
        std::ifstream               m_file;
        std::vector<std::string>    m_raw;
    };
}

#endif //CPP_PLAZZA_FILEREADER_HPP
