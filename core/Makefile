MK_THIS=        ./mk/
MK_COMMON_DIR=  ./../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

SRC=    $(addprefix $(SRC_DIR), \
	ProcessManager.cpp 	\
	Timer.cpp 		\
	)

ifeq ($(UI), yes)

SRC +=    $(addprefix $(SRC_DIR), \
	CoreGui.cpp 		\
	main_plazza_gui.cpp	\
	)

else

SRC +=    $(addprefix $(SRC_DIR), \
	Core.cpp 		\
	main_plazza.cpp 	\
	)

endif

include $(MK_COMMON_DIR)rules.mk
