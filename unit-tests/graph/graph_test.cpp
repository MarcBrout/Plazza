//
// Created by duhieu_b on 18/04/17.
//

#include "gtest/gtest.h"
#include "AGraph.hpp"
#include "Enums.hpp"
#include "graph_test.hpp"

GraphTest::GraphTest() : m_graph(AGraphAst<plazza::Type, std::string>(plazza::COMMA, ";"))
{
}

TEST_F (GraphTest, createGraph)
{
    ASSERT_EQ(m_graph.getGraph().size(), 1);

    EXPECT_EQ(m_graph.getGraph().begin()->s_data.second, ";");
}

TEST_F (GraphTest, addNode)
{
    m_graph.addNode(plazza::ORDER, "PHONE_NUMBER");
    m_graph.addNode(plazza::FILE, "index.htm");
    m_graph.addNode(plazza::FILE, "company.csv");
    ASSERT_EQ(m_graph.getGraph().size(), 1);
    m_graph.simpleLinkNode(plazza::ORDER);
    ASSERT_EQ(m_graph.validNode(), false);
    m_graph.simpleLinkNode(plazza::ORDER);
    ASSERT_EQ(m_graph.validNode(), true);
    ASSERT_EQ(m_graph.getGraph().size(), 1);
    ASSERT_EQ(m_graph.getGraph().begin()->s_link.size(), 1);
    ASSERT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_link.size(), 2);

    EXPECT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_data.second, "PHONE_NUMBER");
    EXPECT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_link.begin()->s_data.second, "index.htm");
    EXPECT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_link.back().s_data.second, "company.csv");
}

TEST_F (GraphTest, deleteNode)
{
    m_graph.deleteNode(plazza::FILE, "index.htm");

    ASSERT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_link.size(), 1);
    EXPECT_EQ(m_graph.getGraph().begin()->s_link.begin()->s_link.back().s_data.second, "company.csv");
    m_graph.deleteNode(plazza::ORDER, "PHONE_NUMBER");
    ASSERT_EQ(m_graph.getGraph().begin()->s_link.size(), 0);
}