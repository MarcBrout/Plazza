//
// Created by duhieu_b on 18/04/17.
//

#ifndef CPP_PLAZZA_GRAPH_TEST_HPP
#define CPP_PLAZZA_GRAPH_TEST_HPP

#include "gtest/gtest.h"
#include "AGraph.hpp"


class GraphTest : public ::testing::Test
{
public:
    GraphTest();
    ~GraphTest() {};
protected:
    AGraphAst<plazza::Type, std::string> m_graph;
};

#endif //CPP_PLAZZA_GRAPH_TEST_HPP
