//
// Created by brout_m on 19/04/17.
//

#include <FileScrapper.hpp>
#include "gtest/gtest.h"
#include "RegexParser.hpp"
#include "FileReader.hpp"

TEST(file_scrapper_test, simple_regex)
{
    std::vector<std::string> l_results;
    plazza::RegexParser     l_regexer("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");

    l_regexer.feed("marc.brout@gmail.com blablabla ben.dudu@fr.eu");
    l_regexer.moveResultsTo(l_results);

    ASSERT_EQ(l_results.size(), 2);
    EXPECT_EQ(l_results[0], "marc.brout@gmail.com");
    EXPECT_EQ(l_results[1], "ben.dudu@fr.eu");
}

TEST(file_scrapper_test, simple_file_read)
{
    std::vector<std::string> l_results;
    plazza::FileReader  l_fileReader("./file_scrapper/fileToReadTest.txt");

    ASSERT_EQ(l_fileReader.isOpen(), true);

    l_fileReader.moveRawTo(l_results);

    ASSERT_EQ(l_results.size(), 7);
    EXPECT_EQ(l_results[0], "bonjour ceci est");
    EXPECT_EQ(l_results[1], "un fichier à lire");
    EXPECT_EQ(l_results[2], "attention");
    EXPECT_EQ(l_results[3], "marc.brout@gmail.com");
    EXPECT_EQ(l_results[4], "à ne pas faire d'erreur");
    EXPECT_EQ(l_results[5], "ben.dudu@fr.eu");
    EXPECT_EQ(l_results[6], "a table");

}

TEST(file_scrapper_test, simple_file_scrapper)
{
    std::vector<std::string>    l_results;
    plazza::RegexParser         l_regexer("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
    plazza::FileScrapper        l_scrapper("./file_scrapper/fileToReadTest.txt", &l_regexer);

    ASSERT_EQ(l_scrapper.isValid(), true);

    l_scrapper.scrapFile();
    l_scrapper.moveResultsTo(l_results);

    ASSERT_EQ(l_results.size(), 2);
    EXPECT_EQ(l_results[0], "marc.brout@gmail.com");
    EXPECT_EQ(l_results[1], "ben.dudu@fr.eu");
}