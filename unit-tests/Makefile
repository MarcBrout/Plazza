TEST = tests

SRC = ./cipher_manager/Cipher_test.cpp \
	./splitter/splitter_test.cpp \
	./file_scrapper/file_scrapper_tests.cpp \
	./thread_pool/thread_pool_tests.cpp \
	./command_generator/command_generator_test.cpp \
	./graph/graph_test.cpp \
	../command_generator/src/Splitter.cpp \
	../command_generator/src/CommandGenerator.cpp \
	../cipher_manager/src/XORCipher.cpp \
	../cipher_manager/src/CesarCipher.cpp \
	../cipher_manager/src/ACipher.cpp \
	../file_scrapper/src/RegexParser.cpp \
	../file_scrapper/src/FileReader.cpp \
	../file_scrapper/src/FileScrapper.cpp

OBJ = $(SRC:.cpp=.o)

INC = -I../interfaces \
	-I../cipher_manager/include \
	-I../command_generator/include \
	-I../thread_pool/include \
	-I../file_scrapper/include

GTEST_DIR = ./googletest

CXX = g++

CXXFLAGS = -std=c++14 -g -Wall -Wextra -pthread

CPPFLAGS += -isystem $(GTEST_DIR)/include $(INC)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(TEST) : $(OBJ) gtest.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -lpthread $^ -o $@

all : $(TEST)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

clean :
	rm -f $(OBJ)
	rm -f gtest-all.o

fclean : clean
	rm -f $(TEST)

re : fclean all

.PHONY: all clean re fclean
