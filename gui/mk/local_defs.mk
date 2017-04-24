SRC_DIR= ./src/

LOCAL_CXXFLAGS= -I./include -I ./../interfaces -I /usr/include/Qt5 -I /usr/include/Qt5/QtWidgets -I /usr/include/qt/QtWidgets/ -lQt5Widgets -fPIC -I /usr/include/qt/  -I ../command_generator/include/ -I ./../ast/include/

LOCAL_CXXFLAGS+= -I ./../core/include -I ./../thread_pool/include/ -I ./../communication/socket_internet/include/ -I ./../logger/include

OBJ_DIR= ./../obj/
