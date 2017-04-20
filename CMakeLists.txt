cmake_minimum_required(VERSION 3.6)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 14)


include_directories(
        /usr/include/Qt5/QtWidgets
        /usr/local/include
        /usr/include
        ./command_generator/include
        ./gui/include
        ./ast/include
        ./interfaces
        ./cipher_manager/include
        ./unit-tests/googletest/include
        ./thread_pool/include
        ./core/include
        ./file_scrapper/include
)

set(CORE
        ./core/include
        ./core/src
        ./main_plazza.cpp
        )

set(FILESCRAPPER
        ./file_scrapper/src
        ./file_scrapper/include
        )

set(THREADPOOL
        ./thread_pool/include
        ./thread_pool/src
        )

set(CMDGEN
        ./command_generator/src
        ./command_generator/include
        )

set(AST
        ./ast/src
        ./ast/include)

set(CIPHERS
        ./cipher_manager/src
        ./cipher_manager/include
        )

set(INTERFACES
        ./interfaces
        )

set(GUI
        ./gui/src/
        main_plazza_gui.cpp
        ./gui/include
        )

set(CIPHERS-TESTS
        ./unit-tests/cipher_manager
        ./unit-tests/googletest/include
        )

set(SPLITTER-TESTS
        ./unit-tests/splitter/splitter_test.cpp
        ./unit-tests/googletest/include
        )

set(THREADPOOL-TESTS
        ./unit-tests/thread_pool/thread_pool_tests.cpp
        ./unit-tests/googletest/include
        )

set(FILESCRAPPER-TESTS
        ./unit-tests/file_scrapper
        ./unit-tests/googletest/include
        )

set(GRAPH_TESTS
        ./unit-tests/graph/graph_test.cpp
        ./unit-tests/googletest/include)

set(SOURCE_FILES
        ${THREADPOOL}
        ${AST}
        ${CMDGEN}
        ${GUI}
        ${INTERFACES}
        ${CIPHERS}
        ${CORE}
        ${FILESCRAPPER}
        )

set(TEST_SOURCE_FILES
        ./unit-tests/cipher_manager/Cipher_test.cpp
        ${INTERFACES}
        ${CIPHERS-TESTS}
        ${CIPHERS}
        )

set(TEST_SPLITTER_SOURCE
        ${INTERFACES}
        ${SPLITTER}
        ${SPLITTER-TESTS}
        )

set(TEST_FILE_SCRAPPER
        ${FILESCRAPPER-TESTS}
        )

set(TEST_COMMAND_GEN_SOURCE
        ./unit-tests/command_generator/command_generator_test.cpp
        ${CMDGEN}
        )

set(TEST_THREAD_POOL
        ${INTERFACES}
        ${THREADPOOL}
        ${THREADPOOL-TESTS}
        )

set(TEST_GRAPH
        ${INTERFACES}
        ${GRAPH_TESTS}
        )

add_executable(plazza ${SOURCE_FILES})

add_executable(cipher_manager_tests ${TEST_SOURCE_FILES})
add_executable(splitter_tests ${TEST_SPLITTER_SOURCE})
add_executable(cmd_gen_tests ${TEST_COMMAND_GEN_SOURCE})
add_executable(thread_pool_test ${TEST_THREAD_POOL})
add_executable(graph_test ${TEST_GRAPH})
add_executable(file_scrapper_test ${TEST_FILE_SCRAPPER})