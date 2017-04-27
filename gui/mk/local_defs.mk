SRC_DIR= ./src/

LOCAL_CXXFLAGS= -I./include -I ./../interfaces -I /usr/include/qt/  -I ../command_generator/include/ -I ./../ast/include/

LOCAL_CXXFLAGS+= -I ./../core/include -I ./../thread_pool/include/ -I ./../communication/socket_internet/include/ -I ./../logger/include

ifeq ($(UI), yes)
 LOCAL_CXXFLAGS += -I /usr/include/Qt5 -I /usr/include/Qt5/QtWidgets -I /usr/include/qt/QtWidgets/ -I/usr/include/Qt5/QtCore -I /usr/include/qt/ -fPIC
 LOCAL_LDFLAGS += -Wl, -rpath=/usr/lib/Qt5 -L/usr/lib/Qt5 -lQt5Widgets -lQt5Core -lQt5Gui
endif


OBJ_DIR= ./../obj/
