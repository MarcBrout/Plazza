//
// Created by brout_m on 12/04/17.
//

#ifndef CPP_PLAZZA_XORCIPHER_TEST_HPP_HPP
#define CPP_PLAZZA_XORCIPHER_TEST_HPP_HPP

#include "gtest/gtest.h"
#include "XORCipher.hpp"
#include "CesarCipher.hpp"

class XORCipherTest : public ::testing::Test
{
public:
    XORCipherTest();
    ~XORCipherTest(){};

protected:
    cipher::XORCipher m_xorCipherTest;
};

#endif //CPP_PLAZZA_XORCIPHER_TEST_HPP_HPP
