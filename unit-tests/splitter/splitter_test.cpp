//
// Created by brout_m on 14/04/17.
//

#include "gtest/gtest.h"
#include "Splitter.hpp"

TEST(SplitterTest, simple_string)
{
    std::string                 stringToSplit {"Ceci est un\nsimple test"};
    Splitter                    splitter;
    std::vector<std::string>    result {};

    splitter.split(stringToSplit, " \n");
    result = splitter.getTokens();

    ASSERT_EQ(result.size(), 5);

    EXPECT_EQ(result[0], "Ceci");
    EXPECT_EQ(result[1], "est");
    EXPECT_EQ(result[2], "un");
    EXPECT_EQ(result[3], "simple");
    EXPECT_EQ(result[4], "test");

    splitter.clear();
}

TEST(SplitterTest, complexe_string)
{
    std::string                 stringToSplit {"  Ceci est\t   un\nsimple test "
                                                       "   plus hard    "};
    Splitter                    splitter;
    std::vector<std::string>    result {};

    splitter.split(stringToSplit, " \n\t");
    result = splitter.getTokens();

    ASSERT_EQ(result.size(), 7);

    EXPECT_EQ(result[0], "Ceci");
    EXPECT_EQ(result[1], "est");
    EXPECT_EQ(result[2], "un");
    EXPECT_EQ(result[3], "simple");
    EXPECT_EQ(result[4], "test");
    EXPECT_EQ(result[5], "plus");
    EXPECT_EQ(result[6], "hard");

    splitter.clear();
}

TEST(SplitterTest, feeding_multiple_strings)
{
    std::string                 stringToSplit {"Ceci est un\nsimple test"};
    std::string                 stringToSplit2 {"  Ceci est\t   un\nsimple "
                                                        "test plus hard    "};
    Splitter                    splitter;
    std::vector<std::string>    result {};

    splitter.split(stringToSplit, " \n\t");
    splitter.split(stringToSplit2, " \n\t");
    result = splitter.getTokens();

    ASSERT_EQ(result.size(), 12);

    EXPECT_EQ(result[0], "Ceci");
    EXPECT_EQ(result[1], "est");
    EXPECT_EQ(result[2], "un");
    EXPECT_EQ(result[3], "simple");
    EXPECT_EQ(result[4], "test");
    EXPECT_EQ(result[5], "Ceci");
    EXPECT_EQ(result[6], "est");
    EXPECT_EQ(result[7], "un");
    EXPECT_EQ(result[8], "simple");
    EXPECT_EQ(result[9], "test");
    EXPECT_EQ(result[10], "plus");
    EXPECT_EQ(result[11], "hard");

    splitter.clear();

}