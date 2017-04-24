OBJ=		$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

ifeq ($(NAME), "tmp")
all:    $(OBJ)
	
endif

ifeq ($(NAME), "plazza")

all:    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ_DIR)*.o $(LDFLAGS) $(LOCAL_LDFLAGS) && echo  -e '\E[30;32m'"\033[1m[OK] $(NAME) with options: $(CXXFLAGS) $(LOCAL_CXXFLAGS) $(LDFLAGS) $(LOCAL_LDFLAGS)\033[0m";echo;

endif

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	        echo "compiling $<"
		$(CXX) -c -o $@ $< $(CXXFLAGS) $(LOCAL_CXXFLAGS)

clean:
	        @$(RM) $(OBJ)
		        @echo -e '\E[30;33m'"\033[1m[OK] Deleting objs\033[0m"

fclean: clean
	        @$(RM) $(NAME)
		        @echo -e '\E[30;33m'"\033[1m[OK] Deleting binary: $(BASE_NAME)\033[0m"

re: fclean all

.PHONY: clean fclean all re
