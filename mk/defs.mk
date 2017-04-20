CXX=            g++

DEBUG=          no

CXXFLAGS=       -W -Wall -Wextra -Wpointer-arith -Weffc++ -std=c++14

LDFLAGS=	""

RM=             rm -f

SRC=            ""

OBJ=            ""

OBJ_PATH=	""

BASE_DIR=       $(CURDIR)

ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g -D DEBUG
endif
