
## Some basic C++ definitions for arcade Makefiles

# MODE

DEBUG	=	NO

RELEASE	=	NO

DLL	= NO

SANITIZE = NO

# NAME

PROJECT_NAME	=

# Compilation definitions

CXXFLAGS	=	-std=c++14 -W -Wall -Wextra
ifeq ($(RELEASE), YES)
CXXFLAGS	+=	-Werror
else
ifeq ($(DEBUG), YES)
CXXFLAGS	+=	-D DEBUG -g
endif
endif
ifeq ($(DLL), YES)
CXXFLAGS	+=	-fPIC -ldl
endif
ifeq ($(STATIC), YES)
CXXFLAGS	+=	-fPIC
endif

ifeq ($(SANITIZE), YES)
CXXFLAGS	+=	-fsanitize=memory -fsanitize-memory-track-origins=2 -fomit-frame-pointer
endif

CXX		=	g++

LDFLAGS	=

ifeq ($(DLL), YES)
CXX	+= -shared
endif

ifeq ($(STATIC), YES)
LINKER = ar -rcs
endif
