OBJ=		$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

ifeq ($(NAME), tmp)
all:    $(OBJ)
	
endif

ifeq ($(NAME), plazza)

all:    $(OBJ)
	@echo "Linking"
	g++ -o ./../$(NAME) ./../obj/*.o $(LDFLAGS) $(LOCAL_LDFLAGS)

endif

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	        echo "compiling $<"
		$(CXX) -c -o $@ $< $(CXXFLAGS) $(LOCAL_CXXFLAGS)

ifeq ($(NAME), tmp)
clean:
	        @$(RM) $(OBJ)
		        @echo -e '\E[30;33m'"\033[1m[OK] Deleting objs\033[0m"

fclean: clean
	@echo -e '\E[30;33m'"\033[1m[OK] No binary to delete\033[0m"
endif

ifeq ($(NAME), plazza)
clean:
	        @$(RM) $(OBJ)
		        @echo -e '\E[30;33m'"\033[1m[OK] Deleting objs\033[0m"

fclean: clean
	        @$(RM) ./../$(NAME)
		        @echo -e '\E[30;33m'"\033[1m[OK] Deleting binary: $(NAME)\033[0m"
endif
re: fclean all

.PHONY: clean fclean all re
# && echo  -e '\E[30;32m'"\033[1m[OK] $(NAME) with options: $(CXXFLAGS) $(LOCAL_CXXFLAGS) $(LDFLAGS) $(LOCAL_LDFLAGS)\033[0m";echo;
