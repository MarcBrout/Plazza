//
// Created by brout_m on 14/04/17.
//

#include "gtest/gtest.h"
#include "CommandGenerator.hpp"

TEST(Command_generator_test, simple_command)
{
    CommandGenerator cmdGen({"ORDER1", "CHAT", "POISSON"});
    std::string files {"lol\n./test fichier\tlo2"};
    std::string result;

    cmdGen.feed(files, "CHAT");
    cmdGen.feed(files, "POISSON");
    result = cmdGen.getCmd();

    ASSERT_EQ(result, "lol ./test fichier lo2 CHAT; lol ./test fichier lo2 "
            "POISSON");
}