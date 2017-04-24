SRC_DIR= ./src/

LOCAL_CXXFLAGS= -I./include -I ./../interfaces -I ./../gui/include -I ./../thread_pool/include -I /usr/include/Qt5 -I /usr/include/Qt5/QtWidgets -I /usr/include/qt/QtWidgets/ -lQt5Widgets -fPIC -I /usr/include/qt/  -I ../command_generator/include/ -I ./../file_scrapper/include -I ./../cipher_manager/include/ -I ./../communication/socket_internet/include/ -I ./../logger/include

LOCAL_LDFLAGS= -lQt5Widgets -pthread

OBJ_DIR= ./../obj/

NAME= plazza
