MK_THIS=        ./mk/
MK_COMMON_DIR=  ./../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

ifeq ($(UI), yes)
  SRC= $(addprefix $(SRC_DIR),	\
	GUI.cpp 		\
	)
else
  SRC= $(addprefix $(SRC_DIR),	\
	NoGUI.cpp 		\
	)
endif

include $(MK_COMMON_DIR)rules.mk
