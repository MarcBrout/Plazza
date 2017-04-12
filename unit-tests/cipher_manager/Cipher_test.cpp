//
// Created by brout_m on 12/04/17.
//

#include "gtest/gtest.h"
#include "Cipher_test.hpp"


XORCipherTest::XORCipherTest() :
        m_xorCipherTest()
{
    m_xorCipherTest.setKey(10);
}


TEST_F (XORCipherTest, ciphering) {
    m_xorCipherTest.feed("bonjour je m'appelle marc");

    std::vector<std::string> l_vector = m_xorCipherTest.cipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test = l_vector[0];

    EXPECT_EQ(l_test, "hed`e\x7Fx*`o*g-kzzoffo*gkxi");

    m_xorCipherTest.clear();

    EXPECT_EQ(m_xorCipherTest.decipher().size(), 0);
}

TEST_F(XORCipherTest, deciphering)
{
    m_xorCipherTest.feed("hed`e\x7Fx*`o*g-kzzoffo*gkxi");

    std::vector<std::string> l_vector = m_xorCipherTest.cipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test = l_vector[0];

    EXPECT_EQ(l_test, "bonjour je m'appelle marc");

    m_xorCipherTest.clear();

    EXPECT_EQ(m_xorCipherTest.decipher().size(), 0);
}

TEST_F(XORCipherTest, multi_inserting)
{
    std::string l_sample("bonjour je m'appelle marc");
    m_xorCipherTest += l_sample;
    m_xorCipherTest += l_sample;
    m_xorCipherTest += l_sample;

    std::vector<std::string> l_test = m_xorCipherTest.cipher();

    ASSERT_EQ(l_test.size(), 3);
    EXPECT_EQ(l_test[0], "hed`e\x7Fx*`o*g-kzzoffo*gkxi");
    EXPECT_EQ(l_test[1], "hed`e\x7Fx*`o*g-kzzoffo*gkxi");
    EXPECT_EQ(l_test[2], "hed`e\x7Fx*`o*g-kzzoffo*gkxi");

    m_xorCipherTest.clear();

    EXPECT_EQ(m_xorCipherTest.decipher().size(), 0);
}

TEST(CesarCipherTest, positiveKeyCiphering)
{
    cipher::CesarCipher l_cesarCipher(3);
    std::string l_sample("bonjour je m'appelle marc");

    l_cesarCipher.feed(l_sample);
    std::vector<std::string> l_vector = l_cesarCipher.cipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test(l_vector[0]);

    EXPECT_EQ(l_test, "erqmrxu#mh#p*dsshooh#pduf");

    l_cesarCipher.clear();

    EXPECT_EQ(l_cesarCipher.cipher().size(), 0);
}

TEST(CesarCipherTest, negativeKeyCiphering)
{
    cipher::CesarCipher l_cesarCipher(-3);
    std::string l_sample("erqmrxu#mh#p*dsshooh#pduf");

    l_cesarCipher.feed(l_sample);
    std::vector<std::string> l_vector = l_cesarCipher.cipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test(l_vector[0]);

    EXPECT_EQ(l_test, "bonjour je m'appelle marc");

    l_cesarCipher.clear();

    EXPECT_EQ(l_cesarCipher.cipher().size(), 0);
}

TEST(CesarCipherTest, positiveKeyDeciphering)
{
    cipher::CesarCipher l_cesarCipher(3);
    std::string l_sample("erqmrxu#mh#p*dsshooh#pduf");

    l_cesarCipher.feed(l_sample);
    std::vector<std::string> l_vector = l_cesarCipher.decipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test(l_vector[0]);

    EXPECT_EQ(l_test, "bonjour je m'appelle marc");

    l_cesarCipher.clear();

    EXPECT_EQ(l_cesarCipher.decipher().size(), 0);
}

TEST(CesarCipherTest, negativeKeyDeciphering)
{
    cipher::CesarCipher l_cesarCipher(-3);
    std::string l_sample("bonjour je m'appelle marc");

    l_cesarCipher.feed(l_sample);
    std::vector<std::string> l_vector = l_cesarCipher.decipher();

    ASSERT_EQ(l_vector.size(), 1);

    std::string l_test(l_vector[0]);

    EXPECT_EQ(l_test, "erqmrxu#mh#p*dsshooh#pduf");

    l_cesarCipher.clear();

    EXPECT_EQ(l_cesarCipher.decipher().size(), 0);
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}