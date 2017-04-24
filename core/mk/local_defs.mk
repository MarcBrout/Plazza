SRC_DIR= ./src/

LOCAL_CXXFLAGS= -I./include -I ./../interfaces -I ./../gui/include -I ./../thread_pool/include -fPIC -I /usr/include/qt/  -I ../command_generator/include/ -I ./../file_scrapper/include -I ./../cipher_manager/include/ -I ./../communication/socket_internet/include/ -I ./../logger/include

LOCAL_LDFLAGS= -pthread

OBJ_DIR= ./../obj/

NAME= plazza
