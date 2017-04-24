SRC_DIR= ./src/

LOCAL_CXXFLAGS= -I./include -I ./../interfaces -fPIC -I /usr/include/qt/  -I ../command_generator/include/ -I ./../ast/include/

LOCAL_CXXFLAGS+= -I ./../core/include -I ./../thread_pool/include/ -I ./../communication/socket_internet/include/ -I ./../logger/include

OBJ_DIR= ./../obj/
