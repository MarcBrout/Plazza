cmake_minimum_required(VERSION 3.6)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 14)


include_directories(
        /home/brout_m/Qt5.7.0/5.7/gcc_64/include/
        /usr/local/include
        /usr/include
        ./gui/include
        ./interfaces
        ./cipher_manager/include
        ./unit-tests/googletest/include)

set(CIPHERS
        ./cipher_manager/src
        ./cipher_manager/include)

set(INTERFACES
        ./interfaces)

set(GUI
        ./gui/src/
        ./gui/src/main.cpp
        ./gui/include)

set(CIPHERS-TESTS
        ./unit-tests/cipher_manager
        ./unit-tests/googletest/include)

set(SOURCE_FILES
        ${GUI}
        ${INTERFACES}
        ${CIPHERS})

set(TEST_SOURCE_FILES
        ./unit-tests/cipher_manager/Cipher_test.cpp
        ${INTERFACES}
        ${CIPHERS-TESTS}
        ${CIPHERS})

add_executable(plazza ${SOURCE_FILES})

add_executable(cipher_manager_tests ${TEST_SOURCE_FILES})

