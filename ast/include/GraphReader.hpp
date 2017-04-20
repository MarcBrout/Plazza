//
// Created by duhieu_b on 18/04/17.
//

#ifndef CPP_PLAZZA_GRAPHREADER_HPP
#define CPP_PLAZZA_GRAPHREADER_HPP


#include <vector>
#include "Enums.hpp"
#include "AGraph.hpp"

class GraphReader
{
private:
    std::vector<std::pair<plazza::Information, std::string>> m_reader;
public:
    GraphReader() = default;
    ~GraphReader() = default;

    void readGraph(AGraphAst<plazza::Type, std::string> &);

    const std::vector<std::pair<plazza::Information, std::string>> &getM_reader() const;
};


#endif //CPP_PLAZZA_GRAPHREADER_HPP
